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
    const glm::vec3& size() const;

    void setData(const std::vector<float>& data);
    void setSizes(const std::vector<float>& tensor_u,
                  const std::vector<float>& tensor_v,
                  const std::vector<float>& tensor_w);

    std::vector<float> vertices(const glm::vec3& baseOffset) const;

private:
    void enableBlock(unsigned int x, unsigned int y, unsigned int z);
    unsigned int blockIndex(unsigned int x, unsigned int y, unsigned int z) const;

private:
    glm::vec3 dims_;
    std::vector<Block> blocks_;
    glm::vec3 size_;

    std::vector<float> tensor_u_;
    std::vector<float> tensor_v_;
    std::vector<float> tensor_w_;
};
