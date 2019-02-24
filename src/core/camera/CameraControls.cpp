#include "CameraControls.h"

#include "I_Camera.h"

namespace {
const double ROTATE_SPEED = 1.0;
const double ZOOM_SCALE = 0.95;
}

CameraControls::CameraControls(I_Camera& camera)
    : camera_(camera)
    , state_(ControlState::None)
    , rotate_(glm::vec2())
    , zoom_(glm::vec2())
    , pan_(glm::vec2())
{
}

void CameraControls::startRotate(double x, double y)
{
    state_ = ControlState::Rotate;
    rotate_ = glm::vec2(x, y);
}

void CameraControls::startPan(double x, double y)
{
    state_ = ControlState::Pan;
    pan_ = glm::vec2(x, y);
}

void CameraControls::move(double x, double y)
{
    glm::vec2 end(x, y);

    switch(state_) {
        case ControlState::Rotate:
        {
            glm::vec2 delta = end - rotate_;
            camera_.rotate(delta, ROTATE_SPEED);
            rotate_ = end;
            break;
        }
        case ControlState::Zoom:
        {
            break;
        }
        case ControlState::Pan:
        {
            glm::vec2 delta = end - pan_;
            camera_.pan(delta);
            pan_ = end;
            break;
        }
        default:
            break;
    }
}

void CameraControls::zoom(double delta)
{
    camera_.zoom(delta, ZOOM_SCALE);
}

void CameraControls::finish()
{
    state_ = ControlState::None;
}

void CameraControls::reset()
{
    state_ = ControlState::None;
}
