#pragma once
#include <glm/glm.hpp>
#include <vector>

struct BoundingBox;

class I_Plot
{
public:
    virtual ~I_Plot() = default;

    virtual void contain(const BoundingBox& boundingBox) = 0;
    virtual void containVertices(const std::vector<float>& vertices) = 0;
    virtual const glm::mat4& model() const = 0;
};
