#include "VoxelEngine.h"

#include "I_Repository.h"

#include <bm-engine/engine.h>

#include <stdio.h>

VoxelEngine::VoxelEngine(I_Repository<bme::Mesh>& repository)
    : repository_(repository)
{
}

IntegerId VoxelEngine::generate(const glm::uvec3& dims)
{
    glm::vec3 axis_u = {1.0, 0.0, 0.0};
    glm::vec3 axis_v = {0.0, 1.0, 0.0};
    glm::vec3 axis_w = {0.0, 0.0, 1.0};
    glm::vec3 corner = {0.0, 0.0, 0.0};
    glm::vec3 block_size = {1.0, 1.0, 1.0};

    bme::RegularBlockModel bm = {
        axis_u,
        axis_v,
        axis_w,
        corner,
        block_size,
        dims,
    };

    std::shared_ptr<bme::Mesh> mesh = bme::generate(bm);
    return repository_.insert(mesh);
}

void VoxelEngine::onChanged(const IntegerId& mesh, const std::function<void()>& cb)
{
}

void VoxelEngine::setData(const IntegerId& mesh, const std::vector<float>& data)
{
    // auto& chunkManager = chunkManagerRepository_.lookup(mesh);
    // chunkManager.setData(data);
}

const bme::Mesh& VoxelEngine::mesh(const IntegerId& id) const
{
    return repository_.lookup(id);
}
