#pragma once

#include <glm/glm.hpp>

class I_Camera
{
public:
    virtual ~I_Camera() = default;

    virtual void rotate(const glm::vec2& delta, double speed) = 0;
    virtual void zoom(double delta, double scale) = 0;
    virtual void pan(const glm::vec2& delta) = 0;

    virtual const glm::mat4& view() = 0;
    virtual const glm::mat4& projection() = 0;
};
