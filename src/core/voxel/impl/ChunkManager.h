#pragma once
#include "I_ChunkManager.h"
#include "Chunk.h"

class ChunkManager : public I_ChunkManager
{
public:
    explicit ChunkManager(const glm::vec3& dims);
    explicit ChunkManager(const std::vector<float>& tensor_u,
                          const std::vector<float>& tensor_v,
                          const std::vector<float>& tensor_w);

    ~ChunkManager() = default;

    void onChanged(const std::function<void()>& cb);
    void setData(const std::vector<float>& data);

    const glm::vec3& dims() const;
    std::vector<float> vertices(unsigned int x, unsigned int y, unsigned int z) const;

private:
    std::vector<float> extractChunkData(
        unsigned int x, unsigned int y, unsigned int z, const std::vector<float>& data);

private:
    std::vector<Chunk> chunks_;
    glm::vec3 dims_;
    glm::vec3 numChunks_;

    std::vector<std::function<void()>> observers_;
};
