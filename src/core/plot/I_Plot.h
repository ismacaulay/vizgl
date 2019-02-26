#pragma once
#include <glm/glm.hpp>
#include <vector>

class I_Plot
{
public:
    virtual ~I_Plot() = default;

    virtual void containVertices(const std::vector<float>& vertices) = 0;
    virtual const glm::mat4& model() const = 0;
};
