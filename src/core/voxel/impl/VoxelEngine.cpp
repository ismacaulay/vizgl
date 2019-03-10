#include "VoxelEngine.h"

#include "I_ChunkManagerFactory.h"
#include "I_ChunkManager.h"
#include "I_Repository.h"
#include "VoxelDefines.h"

#include <stdio.h>

VoxelEngine::VoxelEngine(
    I_ChunkManagerFactory& chunkManagerFactory,
    I_Repository<I_ChunkManager>& chunkManagerRepository)
    : chunkManagerFactory_(chunkManagerFactory)
    , chunkManagerRepository_(chunkManagerRepository)
{
}

IntegerId VoxelEngine::generate(const glm::vec3& dims)
{
    auto chunkManager = chunkManagerFactory_.create(dims);
    return chunkManagerRepository_.insert(chunkManager);
}

void VoxelEngine::onChanged(const IntegerId& mesh, const std::function<void()>& cb)
{
    auto& chunkManager = chunkManagerRepository_.lookup(mesh);
    chunkManager.onChanged(cb);
}

void VoxelEngine::setData(const IntegerId& mesh, const std::vector<float>& data)
{
    auto& chunkManager = chunkManagerRepository_.lookup(mesh);
    chunkManager.setData(data);
}

const glm::vec3& VoxelEngine::dims(const IntegerId& mesh) const
{
    const auto& chunkManager = chunkManagerRepository_.lookup(mesh);
    return chunkManager.dims();
}

const std::vector<float>& VoxelEngine::vertices(const IntegerId& mesh) const
{
    const auto& chunkManager = chunkManagerRepository_.lookup(mesh);
    return chunkManager.vertices();
}

std::vector<float> VoxelEngine::vertices(const IntegerId& mesh, unsigned int x, unsigned int y, unsigned int z) const
{
    const auto& chunkManager = chunkManagerRepository_.lookup(mesh);
    return chunkManager.vertices(x, y, z);
}
