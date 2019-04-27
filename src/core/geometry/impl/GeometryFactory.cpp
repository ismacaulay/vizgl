#include "GeometryFactory.h"

#include "I_VoxelEngine.h"
#include "MeshGeometry.h"
#include "VoxelGeometry.h"

#include <stdio.h>

GeometryFactory::GeometryFactory(I_VoxelEngine& voxelEngine)
    : voxelEngine_(voxelEngine)
{
}

std::shared_ptr<I_Geometry> GeometryFactory::createMesh(const std::vector<float>& vertices)
{
    return std::make_shared<MeshGeometry>(vertices);
}

std::shared_ptr<I_VoxelGeometry> GeometryFactory::createBlockModel(const glm::vec3& dims)
{
    auto id = voxelEngine_.generate(dims);
    return std::make_shared<VoxelGeometry>(id, voxelEngine_);
}
