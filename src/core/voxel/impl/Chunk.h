#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "Block.h"

class Chunk
{
public:
    explicit Chunk(const glm::vec3& dims);
    ~Chunk() = default;

    const glm::vec3& dims() const;

    void setData(const std::vector<float>& data);

    std::vector<float> vertices(const glm::vec3& baseOffset) const;

private:
    void enableBlock(unsigned int x, unsigned int y, unsigned int z);
    unsigned int blockIndex(unsigned int x, unsigned int y, unsigned int z) const;

private:
    glm::vec3 dims_;
    std::vector<Block> blocks_;
};
