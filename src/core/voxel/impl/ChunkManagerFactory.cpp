#include "ChunkManagerFactory.h"

#include "ChunkManager.h"

std::shared_ptr<I_ChunkManager> ChunkManagerFactory::create(const glm::vec3& dims)
{
    return std::make_shared<ChunkManager>(dims);
}


std::shared_ptr<I_ChunkManager> ChunkManagerFactory::create(
    const std::vector<float>& tensor_u,
    const std::vector<float>& tensor_v,
    const std::vector<float>& tensor_w)
{
    return std::make_shared<ChunkManager>(tensor_u, tensor_v, tensor_w);
}
