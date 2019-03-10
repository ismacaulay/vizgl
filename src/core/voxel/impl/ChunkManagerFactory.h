#pragma once
#include "I_ChunkManagerFactory.h"

class ChunkManagerFactory : public I_ChunkManagerFactory
{
public:
    explicit ChunkManagerFactory() = default;
    ~ChunkManagerFactory() = default;

    std::shared_ptr<I_ChunkManager> create(const glm::vec3& dims);
};
