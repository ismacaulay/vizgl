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

std::shared_ptr<I_VoxelGeometry> GeometryFactory::createVoxelMesh(const glm::vec3& dims)
{
    auto id = voxelEngine_.generate(dims);
    return std::make_shared<VoxelGeometry>(id, voxelEngine_);
}

std::shared_ptr<I_VoxelGeometry> GeometryFactory::createVoxelMesh(const std::vector<float>& tensor_u,
                                                                  const std::vector<float>& tensor_v,
                                                                  const std::vector<float>& tensor_w)
{
    auto id = voxelEngine_.generate(tensor_u, tensor_v, tensor_w);
    return std::make_shared<VoxelGeometry>(id, voxelEngine_);
}
