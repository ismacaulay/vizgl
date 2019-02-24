#include "Core.h"

#include "Camera.h"
#include "CameraControls.h"
#include "CameraController.h"
#include "Renderer.h"
#include "ViewFactory.h"
#include "ViewManager.h"
#include "ViewRenderer.h"
#include "ViewRepository.h"

class Core::Impl
{
public:
    Impl()
        : camera(45.0, 800.0, 600.0, 0.1f, 100.0f)
        , cameraControls(camera)
        , cameraController(cameraControls)

        , renderer(camera)

        , viewRepository()
        , viewFactory()
        , viewManager(viewFactory, viewRepository)

        , viewRenderer(renderer, viewRepository)
    {
    }

    void run()
    {
        viewRenderer.render();
    }

    Camera camera;
    CameraControls cameraControls;
    CameraController cameraController;

    Renderer renderer;

    ViewRepository viewRepository;
    ViewFactory viewFactory;
    ViewManager viewManager;

    ViewRenderer viewRenderer;
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

void Core::run()
{
    p_->run();
}

ViewManager& Core::viewManager() const
{
    return p_->viewManager;
}

CameraController& Core::cameraController() const
{
    return p_->cameraController;
}
