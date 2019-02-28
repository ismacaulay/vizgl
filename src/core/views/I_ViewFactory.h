#pragma once

#include <vector>
#include <glm/glm.hpp>

class I_View;

class I_ViewFactory
{
public:
    virtual ~I_ViewFactory() = default;

    virtual I_View* createMesh(
        const std::vector<float>& vertices,
        const glm::vec4& color) = 0;
};
