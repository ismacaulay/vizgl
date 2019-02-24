#pragma once
#include "I_Camera.h"
#include <algorithm>

class Camera : public I_Camera
{
public:
    Camera(double fov, double width, double height, double near, double far);
    ~Camera() = default;

    void updateAspectRatio(int width, int height);

    void rotate(const glm::vec2& delta, double speed);
    void zoom(double delta, double scale);
    void pan(const glm::vec2& delta);

    void update();

    const glm::mat4& view();
    const glm::mat4& projection();

private:
    void updateMatrix();

private:
    double fov_;
    double width_;
    double height_;
    double near_;
    double far_;

    glm::mat4 proj_;
    glm::mat4 view_;

    glm::vec3 target_;
    glm::vec3 position_;

    glm::vec3 sphericalDelta_;
    glm::vec3 panDelta_;
    double scale_;
};
