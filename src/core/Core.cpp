#include "Core.h"

#include "Camera.h"
#include "CameraController.h"
#include "CameraControls.h"
#include "Plot.h"
// #include "RenderableRepository.h"
#include "Renderer.h"
// #include "ViewFactory.h"
// #include "ViewManager.h"
#include "OrthographicCamera.h"

#include "GenericRepository.h"
#include "ModelRendererFactory.h"
#include "ShaderManager.h"
#include "ModelManager.h"
#include "ModelFactory.h"
#include "ShaderFactory.h"
#include "MappingFactory.h"
#include "MappingManager.h"
#include "GeometryFactory.h"
#include "GeometryManager.h"
#include "ColorMapFactory.h"
#include "ColorMapManager.h"

#include "I_Geometry.h"
#include "I_Mapping.h"
#include "I_Model.h"
#include "I_ModelRenderer.h"
#include "I_Shader.h"

class Core::Impl
{
public:
    Impl()
        : plot()

        , camera()
        , cameraControls(camera)
        , cameraController(cameraControls)

        , geometryFactory()
        , geometryManager(
            geometryFactory,
            geometryRepository)

        , colorMapFactory()
        , colorMapManager(
            colorMapFactory,
            colorMapRepository)

        , mappingFactory()
        , mappingManager(
            mappingFactory,
            mappingRepository)

        , shaderFactory()
        , shaderManager(
            mappingRepository,
            shaderFactory,
            shaderRepository)

        , modelRendererFactory(
            geometryRepository,
            shaderRepository,
            mappingRepository)

        , modelFactory()
        , modelManager(
            modelFactory,
            modelRepository,
            shaderManager,
            modelRendererFactory,
            modelRendererRepository,
            plot,
            geometryRepository)



        , renderer(camera, plot, modelRendererRepository)
    {
    }

    void render()
    {
        camera.update();
        renderer.render();
    }

    Plot plot;

    // Camera camera;
    OrthographicCamera camera;
    CameraControls cameraControls;
    CameraController cameraController;

    GenericRepository<I_ColorMap> colorMapRepository;
    GenericRepository<I_Geometry> geometryRepository;
    GenericRepository<I_Mapping> mappingRepository;
    GenericRepository<I_Model> modelRepository;
    GenericRepository<I_ModelRenderer> modelRendererRepository;
    GenericRepository<I_Shader> shaderRepository;

    GeometryFactory geometryFactory;
    GeometryManager geometryManager;

    ColorMapFactory colorMapFactory;
    ColorMapManager colorMapManager;

    MappingFactory mappingFactory;
    MappingManager mappingManager;

    ShaderFactory shaderFactory;
    ShaderManager shaderManager;

    ModelRendererFactory modelRendererFactory;

    ModelFactory modelFactory;
    ModelManager modelManager;

    Renderer renderer;

};

Core::Core()
    : p_(std::make_unique<Impl>())
{
}
Core::~Core()
{
}

void Core::setSize(int width, int height)
{
    p_->renderer.setSize(width, height);
    p_->camera.updateAspectRatio(width, height);
}

void Core::render()
{
    p_->render();
}

I_GeometryApi& Core::geometryApi() const
{
    return p_->geometryManager;
}

I_MappingApi& Core::mappingApi() const
{
    return p_->mappingManager;
}

I_ModelApi& Core::modelApi() const
{
    return p_->modelManager;
}

I_CameraApi& Core::cameraApi() const
{
    return p_->cameraController;
}

I_PlotApi& Core::plotApi() const
{
    return p_->plot;
}
