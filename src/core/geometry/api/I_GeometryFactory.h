#pragma once
#include <memory>
#include <vector>
#include <glm/glm.hpp>

class I_Geometry;

class I_GeometryFactory
{
public:
    virtual ~I_GeometryFactory() = default;

    virtual std::shared_ptr<I_Geometry> createMesh(const std::vector<float>& vertices) = 0;
    virtual std::shared_ptr<I_Geometry> createVoxelMesh(const glm::vec3& dims) = 0;
};
