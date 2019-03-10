#pragma once
#include <memory>
#include <glm/glm.hpp>

class I_ChunkManager;

class I_ChunkManagerFactory
{
public:
    virtual ~I_ChunkManagerFactory() = default;

    virtual std::shared_ptr<I_ChunkManager> create(const glm::vec3& dims) = 0;
};
