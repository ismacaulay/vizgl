#pragma once
#include <memory>
#include <vector>
#include <glm/glm.hpp>

class I_Geometry;
class I_VoxelGeometry;

class I_GeometryFactory
{
public:
    virtual ~I_GeometryFactory() = default;

    virtual std::shared_ptr<I_Geometry> createMesh(const std::vector<float>& vertices) = 0;
    virtual std::shared_ptr<I_VoxelGeometry> createVoxelMesh(const glm::vec3& dims) = 0;
    virtual std::shared_ptr<I_VoxelGeometry> createVoxelMesh(const std::vector<float>& tensor_u,
                                                             const std::vector<float>& tensor_v,
                                                             const std::vector<float>& tensor_w) = 0;
};
