#pragma once
#include "IntegerId.h"
#include <glm/glm.hpp>
#include <vector>

class I_VoxelEngine
{
public:
    virtual ~I_VoxelEngine() = default;

    virtual IntegerId generate(const glm::vec3& dims) = 0;

    virtual const std::vector<float>& vertices(const IntegerId& mesh) const = 0;
};
