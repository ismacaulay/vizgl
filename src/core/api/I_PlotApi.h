#pragma once
#include <glm/glm.hpp>

class I_PlotApi
{
public:
    virtual ~I_PlotApi() = default;

    virtual void setRotation(const glm::vec3& rotation) = 0;
};
