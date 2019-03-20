#include "Chunk.h"

#include "VoxelDefines.h"
#include "ArrayUtils.h"
#include "MathUtils.h"

#include <stdio.h>

Chunk::Chunk(const glm::vec3& dims)
    : dims_(dims)
    , size_(dims)

    , tensor_u_(dims.x, 1.0)
    , tensor_v_(dims.y, 1.0)
    , tensor_w_(dims.z, 1.0)
{
    const unsigned int totalBlocks = Voxel::CHUNK_SIZE * Voxel::CHUNK_SIZE * Voxel::CHUNK_SIZE;
    blocks_.reserve(totalBlocks);
    for(int i = 0; i < totalBlocks; i++) {
        blocks_.emplace_back();
    }

    for(int k = 0; k < dims.z; k++) {
        for(int j = 0; j < dims.y; j++) {
            for(int i = 0; i < dims.x; i++) {
                enableBlock(i, j, k);
            }
        }
    }
}

const glm::vec3& Chunk::dims() const
{
    return dims_;
}

const glm::vec3& Chunk::size() const
{
    return size_;
}

void Chunk::setData(const std::vector<float>& data)
{
    if (data.size() < dims_.x * dims_.y * dims_.z) {
        printf("[Chunk] invalid data size: got %lu, expected %f %f %f (%f)\n", data.size(), dims_.x, dims_.y, dims_.z, (dims_.x * dims_.y * dims_.z));
        return;
    }

    for(auto& block : blocks_) {
        block.setActive(false);
    }

    for(int i = 0; i < dims_.x; i++) {
        for(int j = 0; j < dims_.y; j++) {
            for(int k = 0; k < dims_.z; k++) {
                unsigned int index = ArrayUtils::calculateIndex(i, j, k, dims_);
                float value = data[index];
                if (!std::isnan(value)) {
                    unsigned int index = blockIndex(i, j, k);
                    auto& block = blocks_[index];
                    block.setActive(true);
                    block.setValue(value);
                }
            }
        }
    }
}

void Chunk::setSizes(const std::vector<float>& tensor_u,
                     const std::vector<float>& tensor_v,
                     const std::vector<float>& tensor_w)
{
    tensor_u_ = tensor_u;
    tensor_v_ = tensor_v;
    tensor_w_ = tensor_w;

    for(int i = 0; i < dims_.x; i++) {
        for(int j = 0; j < dims_.y; j++) {
            for(int k = 0; k < dims_.z; k++) {
                unsigned int blockIdx = blockIndex(i, j, k);
                glm::vec3 size(tensor_u[i], tensor_v[j], tensor_w[k]);
                blocks_[blockIdx].setSize(size);
            }
        }
    }

    size_ = glm::vec3(MathUtils::sum(tensor_u), MathUtils::sum(tensor_v), MathUtils::sum(tensor_w));
}

void Chunk::enableBlock(unsigned int x, unsigned int y, unsigned int z)
{
    unsigned int index = blockIndex(x, y, z);
    blocks_[index].setActive(true);
}

std::vector<float> Chunk::vertices(const glm::vec3& baseOffset) const
{
    std::vector<float> verts;
    const auto addFace = [&verts](glm::vec3 t1[3], glm::vec3 t2[3], float value) {
        // triangle 1
        glm::vec3 p0 = t1[0];
        glm::vec3 p1 = t1[1];
        glm::vec3 p2 = t1[2];

        verts.push_back(p0.x); verts.push_back(p0.y); verts.push_back(p0.z);
        verts.push_back(1.0); verts.push_back(1.0); verts.push_back(0.0);
        verts.push_back(value); verts.push_back(value); verts.push_back(value);

        verts.push_back(p1.x); verts.push_back(p1.y); verts.push_back(p1.z);
        verts.push_back(1.0); verts.push_back(0.0); verts.push_back(0.0);
        verts.push_back(value); verts.push_back(value); verts.push_back(value);

        verts.push_back(p2.x); verts.push_back(p2.y); verts.push_back(p2.z);
        verts.push_back(1.0); verts.push_back(0.0); verts.push_back(1.0);
        verts.push_back(value); verts.push_back(value); verts.push_back(value);

        // triangle 2
        p0 = t2[0];
        p1 = t2[1];
        p2 = t2[2];

        verts.push_back(p0.x); verts.push_back(p0.y); verts.push_back(p0.z);
        verts.push_back(1.0); verts.push_back(1.0); verts.push_back(0.0);
        verts.push_back(value); verts.push_back(value); verts.push_back(value);

        verts.push_back(p1.x); verts.push_back(p1.y); verts.push_back(p1.z);
        verts.push_back(1.0); verts.push_back(0.0); verts.push_back(0.0);
        verts.push_back(value); verts.push_back(value); verts.push_back(value);

        verts.push_back(p2.x); verts.push_back(p2.y); verts.push_back(p2.z);
        verts.push_back(1.0); verts.push_back(0.0); verts.push_back(1.0);
        verts.push_back(value); verts.push_back(value); verts.push_back(value);
    };

    for(int k = 0; k < Voxel::CHUNK_SIZE; k++) {
        float zOffset = MathUtils::sum_to_index(tensor_w_, k);
        for(int j = 0; j < Voxel::CHUNK_SIZE; j++) {
            float yOffset = MathUtils::sum_to_index(tensor_v_, j);
            for(int i = 0; i < Voxel::CHUNK_SIZE; i++) {
                unsigned int index = blockIndex(i, j, k);
                const auto& block = blocks_[index];
                if (block.isActive()) {
                    float xOffset = MathUtils::sum_to_index(tensor_u_, i);
                    glm::vec3 offset = baseOffset + glm::vec3(xOffset, yOffset, zOffset);
                    glm::vec3 p0 = block.getVertex(0, offset);
                    glm::vec3 p1 = block.getVertex(1, offset);
                    glm::vec3 p2 = block.getVertex(2, offset);
                    glm::vec3 p3 = block.getVertex(3, offset);
                    glm::vec3 p4 = block.getVertex(4, offset);
                    glm::vec3 p5 = block.getVertex(5, offset);
                    glm::vec3 p6 = block.getVertex(6, offset);
                    glm::vec3 p7 = block.getVertex(7, offset);
                    float value = block.value();

                    bool addFrontFace = true;
                    if (k > 0) {
                        addFrontFace = !blocks_[blockIndex(i, j, k-1)].isActive();
                    }
                    if(addFrontFace) {
                        glm::vec3 t1[3] = { p0, p1, p2 };
                        glm::vec3 t2[3] = { p2, p3, p0 };
                        addFace(t1, t2, value);
                    }

                    bool addBackFace = true;
                    if (k < Voxel::CHUNK_SIZE - 1) {
                        addBackFace = !blocks_[blockIndex(i, j, k+1)].isActive();
                    }
                    if (addBackFace) {
                        glm::vec3 t1[3] = {p5, p4, p7};
                        glm::vec3 t2[3] = {p7, p6, p5};
                        addFace(t1, t2, value);
                    }

                    bool addLeftFace = true;
                    if (i > 0) {
                        addLeftFace = !blocks_[blockIndex(i-1, j, k)].isActive();
                    }
                    if(addLeftFace) {
                        glm::vec3 t1[3] = {p4, p0, p3};
                        glm::vec3 t2[3] = {p3, p7, p4};
                        addFace(t1, t2, value);
                    }

                    bool addRightFace = true;
                    if (i < Voxel::CHUNK_SIZE - 1) {
                        addRightFace = !blocks_[blockIndex(i+1, j, k)].isActive();
                    }
                    if(addRightFace) {
                        glm::vec3 t1[3] = {p1, p5, p6};
                        glm::vec3 t2[3] = {p6, p2, p1};
                        addFace(t1, t2, value);
                    }

                    bool addTopFace = true;
                    if (j < Voxel::CHUNK_SIZE - 1) {
                        addTopFace = !blocks_[blockIndex(i, j+1, k)].isActive();
                    }
                    if(addTopFace) {
                        glm::vec3 t1[3] = {p3, p2, p6};
                        glm::vec3 t2[3] = {p6, p7, p3};
                        addFace(t1, t2, value);
                    }

                    bool addBottomFace = true;
                    if (j > 0) {
                        addBottomFace = !blocks_[blockIndex(i, j-1, k)].isActive();
                    }
                    if (addBottomFace) {
                        glm::vec3 t1[3] = {p0, p4, p5};
                        glm::vec3 t2[3] = {p5, p1, p0};
                        addFace(t1, t2, value);
                    }
                }
            }
        }
    }

    return verts;
}

unsigned int Chunk::blockIndex(unsigned int x, unsigned int y, unsigned int z) const
{
    static glm::vec3 dims(Voxel::CHUNK_SIZE, Voxel::CHUNK_SIZE, Voxel::CHUNK_SIZE);
    return ArrayUtils::calculateIndex(x, y, z, dims);
}
