#include "Core.h"

#include "Camera.h"
#include "CameraController.h"
#include "CameraControls.h"
#include "RenderableRepository.h"
#include "Renderer.h"
#include "ViewFactory.h"
#include "ViewManager.h"

class Core::Impl
{
public:
    Impl()
        : camera(45.0, 800.0, 600.0, 0.1f, 100.0f)
        , cameraControls(camera)
        , cameraController(cameraControls)

        , renderableRepository()
        , renderer(camera, renderableRepository)

        , viewFactory()
        , viewManager(viewFactory, renderableRepository)
    {
    }

    void render()
    {
        camera.update();
        renderer.render();
    }

    Camera camera;
    CameraControls cameraControls;
    CameraController cameraController;

    RenderableRepository renderableRepository;
    Renderer renderer;

    ViewFactory viewFactory;
    ViewManager viewManager;

private:
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

I_ViewApi& Core::viewApi() const
{
    return p_->viewManager;
}

I_CameraApi& Core::cameraApi() const
{
    return p_->cameraController;
}
