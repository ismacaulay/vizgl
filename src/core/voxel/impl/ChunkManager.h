#pragma once
#include "I_ChunkManager.h"
#include "Chunk.h"

class ChunkManager : public I_ChunkManager
{
public:
    explicit ChunkManager(const glm::vec3& dims);
    ~ChunkManager() = default;

    void onChanged(const std::function<void()>& cb);
    void setData(const std::vector<float>& data);

    const glm::vec3& dims() const;
    std::vector<float> vertices(unsigned int x, unsigned int y, unsigned int z) const;

private:
    Chunk createChunk(const glm::vec3& dims);
    void updateMesh();

private:
    std::vector<Chunk> chunks_;
    glm::vec3 dims_;

    std::vector<std::function<void()>> observers_;
};
