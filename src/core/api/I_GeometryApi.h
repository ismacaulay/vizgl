#pragma once
#include "IntegerId.h"
#include <glm/glm.hpp>
#include <vector>

class I_GeometryApi
{
public:
    virtual ~I_GeometryApi() = default;

    virtual IntegerId createMesh(const std::vector<float>& vertices) = 0;
    virtual IntegerId createMesh(const std::vector<float>& vertices,
                                 const std::vector<uint32_t>& triangles) = 0;

    virtual IntegerId createVoxelMesh(const glm::vec3& dims) = 0;
};
