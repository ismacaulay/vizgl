#pragma once
#include "I_GeometryFactory.h"

class I_VoxelEngine;

class GeometryFactory : public I_GeometryFactory
{
public:
    explicit GeometryFactory(I_VoxelEngine& voxelEngine);
    ~GeometryFactory() = default;

    std::shared_ptr<I_Geometry> createMesh(const std::vector<float>& vertices);
    std::shared_ptr<I_VoxelGeometry> createVoxelMesh(const glm::vec3& dims);

private:
    I_VoxelEngine& voxelEngine_;
};
