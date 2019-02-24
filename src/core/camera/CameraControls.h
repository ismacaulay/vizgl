#pragma once
#include "I_CameraControls.h"

#include <glm/glm.hpp>

class I_Camera;

class CameraControls : public I_CameraControls
{
public:
    CameraControls(I_Camera& camera);
    ~CameraControls() = default;

    void startRotate(double x, double y);
    void startPan(double x, double y);
    void move(double x, double y);

    void zoom(double delta);

    void finish();
    void reset();

private:
    enum class ControlState {
        None,
        Rotate,
        Pan,
        Zoom,
    };

    I_Camera& camera_;
    ControlState state_;
    glm::vec2 rotate_;
    glm::vec2 zoom_;
    glm::vec2 pan_;
};
