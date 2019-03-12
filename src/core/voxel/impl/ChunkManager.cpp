#include "ChunkManager.h"

#include "ArrayUtils.h"
#include "VoxelDefines.h"

#include <stdio.h>

glm::vec3 calculateNumberOfChunks(const glm::vec3& dims)
{
    unsigned int x = std::ceil(static_cast<float>(dims.x)/static_cast<float>(Voxel::CHUNK_SIZE));
    unsigned int y = std::ceil(static_cast<float>(dims.y)/static_cast<float>(Voxel::CHUNK_SIZE));
    unsigned int z = std::ceil(static_cast<float>(dims.z)/static_cast<float>(Voxel::CHUNK_SIZE));
    return glm::vec3(x, y, z);
}

glm::vec3 calculateChunkDims(unsigned int x, unsigned int y, unsigned int z, const glm::vec3& dims)
{
    auto calulateDim = [](unsigned int index, unsigned int dim) {
        unsigned int remaining = dim - (index * Voxel::CHUNK_SIZE);
        return remaining > Voxel::CHUNK_SIZE ? Voxel::CHUNK_SIZE : remaining;
    };

    unsigned int dimX = calulateDim(x, dims.x);
    unsigned int dimY = calulateDim(y, dims.y);
    unsigned int dimZ = calulateDim(z, dims.z);
    return glm::vec3(dimX, dimY, dimZ);
}

ChunkManager::ChunkManager(const glm::vec3& dims)
{
    dims_ = calculateNumberOfChunks(dims);
    for(int k = 0; k < dims_.z; k++) {
        for(int j = 0; j < dims_.y; j++) {
            for(int i = 0; i < dims_.x; i++) {
                glm::vec3 chunkDims = calculateChunkDims(i, j, k, dims);
                chunks_.emplace_back(chunkDims);
            }
        }
    }
}

void ChunkManager::onChanged(const std::function<void()>& cb)
{
    observers_.push_back(cb);
}

void ChunkManager::setData(const std::vector<float>& data)
{
    unsigned int offset = 0;
    for(int k = 0; k < dims_.z; k++) {
        for(int j = 0; j < dims_.y; j++) {
            for(int i = 0; i < dims_.x; i++) {
                unsigned int chunkIdx = ArrayUtils::calculateIndex(i, j, k, dims_);
                auto& chunk = chunks_[chunkIdx];
                auto& chunkDims = chunk.dims();

                unsigned int endOffset = chunkDims.x * chunkDims.y * chunkDims.z;
                std::vector<float> chunkData(
                    data.begin() + offset,
                    data.begin() + offset + endOffset
                );
                chunk.setData(chunkData);

                offset += endOffset;
            }
        }
    }

    for (const auto& cb : observers_) {
        cb();
    }
}

const glm::vec3& ChunkManager::dims() const
{
    return dims_;
}

std::vector<float> ChunkManager::vertices(unsigned int x, unsigned int y, unsigned int z) const
{
    unsigned int chunkIdx = ArrayUtils::calculateIndex(x, y, z, dims_);
    auto chunk = chunks_[chunkIdx];
    return chunk.vertices(glm::vec3(x, y, z));
}
