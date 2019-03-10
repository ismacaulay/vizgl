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

const std::vector<float>& VoxelEngine::vertices(const IntegerId& mesh) const
{
    const auto& chunkManager = chunkManagerRepository_.lookup(mesh);
    return chunkManager.vertices();
}
