#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "Block.h"

class Chunk
{
public:
    explicit Chunk();
    ~Chunk() = default;

    void enableBlock(unsigned int x, unsigned int y, unsigned int z);

    std::vector<float> vertices(const glm::vec3& baseOffset) const;

private:
    unsigned int blockIndex(unsigned int x, unsigned int y, unsigned int z) const;

private:
    std::vector<Block> blocks_;
};
