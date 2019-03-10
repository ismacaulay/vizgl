#include "ChunkManagerFactory.h"

#include "ChunkManager.h"

std::shared_ptr<I_ChunkManager> ChunkManagerFactory::create(const glm::vec3& dims)
{
    return std::make_shared<ChunkManager>(dims);
}
