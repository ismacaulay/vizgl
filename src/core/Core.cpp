#include "Core.h"

#include "Camera.h"
#include "CameraController.h"
#include "CameraControls.h"
#include "ColorMapFactory.h"
#include "ColorMapManager.h"
#include "GenericRepository.h"
#include "GeometryFactory.h"
#include "GeometryManager.h"
#include "I_Geometry.h"
#include "I_Mapping.h"
#include "I_Model.h"
#include "I_ModelRenderer.h"
#include "I_Shader.h"
#include "IdLookupTable.h"
#include "MappingFactory.h"
#include "MappingManager.h"
#include "ModelFactory.h"
#include "ModelManager.h"
#include "ModelRenderer.h"
#include "ModelRendererFactory.h"
#include "OrthographicCamera.h"
#include "Plot.h"
#include "Renderer.h"
#include "ShaderBinder.h"
#include "ShaderFactory.h"
#include "ShaderManager.h"
#include "VoxelEngine.h"

class Core::Impl
{
public:
    Impl()
        : plot()

        , camera()
        , cameraControls(
            camera)
        , cameraController(
            cameraControls)

        , colorMapRepository()
        , geometryRepository()
        , mappingRepository()
        , modelRepository()
        , shaderRepository()
        , blockmodelMeshRepository()

        , geometryToVoxelMeshLookupTable()

        , voxelEngine(blockmodelMeshRepository)

        , geometryFactory(
            voxelEngine)
        , geometryManager(
            geometryFactory,
            geometryRepository,
            geometryToVoxelMeshLookupTable)

        , colorMapFactory()
        , colorMapManager(
            colorMapFactory,
            colorMapRepository)

        , mappingFactory(
            colorMapRepository,
            geometryToVoxelMeshLookupTable,
            voxelEngine)
        , mappingManager(
            mappingFactory,
            mappingRepository)

        , shaderFactory()
        , shaderManager(
            mappingRepository,
            shaderFactory,
            shaderRepository)
        , shaderBinder(
            shaderRepository)

        , modelRenderer(
            geometryRepository,
            mappingRepository)
        , modelFactory()
        , modelManager(
            modelFactory,
            modelRepository,
            shaderManager,
            plot,
            geometryRepository)

        , renderer(
            camera,
            plot,
            shaderBinder,
            modelRenderer,
            modelRepository)
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
    GenericRepository<I_Shader> shaderRepository;
    GenericRepository<bme::Mesh> blockmodelMeshRepository;

    IdLookupTable geometryToVoxelMeshLookupTable;

    VoxelEngine voxelEngine;

    GeometryFactory geometryFactory;
    GeometryManager geometryManager;

    ColorMapFactory colorMapFactory;
    ColorMapManager colorMapManager;

    MappingFactory mappingFactory;
    MappingManager mappingManager;

    ShaderFactory shaderFactory;
    ShaderManager shaderManager;
    ShaderBinder shaderBinder;

    ModelRenderer modelRenderer;
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

I_ColorMapApi& Core::colorMapApi() const
{
    return p_->colorMapManager;
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
