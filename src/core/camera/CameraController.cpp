#include "CameraController.h"

#include "I_CameraControls.h"

namespace {
    enum class Button {
        Left = 0,
        Middle = 1,
        Right = 2,
    };
}

CameraController::CameraController(I_CameraControls& cameraControls)
    : cameraControls_(cameraControls)
    , inProgress_(false)
{
}

void CameraController::start(int button, int x, int y)
{
    if (inProgress_)
        return;

    inProgress_ = true;
    switch(static_cast<Button>(button)) {
        case Button::Left:
            cameraControls_.startRotate(x, y);
            break;
        case Button::Middle:
            break;
        case Button::Right:
            cameraControls_.startPan(x, y);
            break;
    }
}

void CameraController::zoom(double delta)
{
    cameraControls_.zoom(delta);
}

void CameraController::update(int x, int y)
{
    if (!inProgress_)
        return;

    cameraControls_.move(x, y);
}

void CameraController::finish()
{
    inProgress_ = false;
    cameraControls_.finish();
}
