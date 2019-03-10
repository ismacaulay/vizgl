#pragma once
#include "I_ChunkManager.h"
#include "Chunk.h"

class ChunkManager : public I_ChunkManager
{
public:
    explicit ChunkManager(const glm::vec3& dims);
    ~ChunkManager() = default;

    const std::vector<float>& vertices() const;

private:
    void updateMesh();

private:
    std::vector<Chunk> chunks_;
    glm::vec3 chunkDims_;

    std::vector<float> vertices_;
};
