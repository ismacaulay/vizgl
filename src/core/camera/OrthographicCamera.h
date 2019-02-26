#pragma once
#include "I_Camera.h"
#include <algorithm>

class OrthographicCamera : public I_Camera
{
public:
    OrthographicCamera();
    ~OrthographicCamera() = default;

    void updateAspectRatio(int width, int height);

    void rotate(const glm::vec2& delta, double speed);
    void zoom(double delta, double scale);
    void pan(const glm::vec2& delta);

    void update();

    const glm::mat4& view() const;
    const glm::mat4& projection() const;

private:
    void updateMatrix();

private:
    double width_, height_;
    double left_, right_;
    double bottom_, top_;
    double near_, far_;
    double zoom_;

    glm::mat4 view_;
    glm::mat4 proj_;

    glm::vec3 target_;
    glm::vec3 position_;

    glm::vec3 sphericalDelta_;
    glm::vec3 panDelta_;
    double scale_;
};
