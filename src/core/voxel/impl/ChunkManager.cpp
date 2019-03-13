#include "ChunkManager.h"

#include "ArrayUtils.h"
#include "VoxelDefines.h"

#include <stdio.h>

glm::vec3 calculateNumberOfChunks(const glm::vec3& dims)
{
    unsigned int x = (dims.x + (Voxel::CHUNK_SIZE - 1))/Voxel::CHUNK_SIZE;
    unsigned int y = (dims.y + (Voxel::CHUNK_SIZE - 1))/Voxel::CHUNK_SIZE;
    unsigned int z = (dims.z + (Voxel::CHUNK_SIZE - 1))/Voxel::CHUNK_SIZE;
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
    dims_ = dims;
    numChunks_ = calculateNumberOfChunks(dims);
    printf("[ChunkManager] num chunks: %f %f %f\n", numChunks_.x,  numChunks_.y,  numChunks_.z);
    for (int i = 0; i < numChunks_.x; i++) {
        for (int j = 0; j < numChunks_.y; j++) {
            for (int k = 0; k < numChunks_.z; k++) {
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
    for (int i = 0; i < numChunks_.x; i++) {
        for (int j = 0; j < numChunks_.y; j++) {
            for (int k = 0; k < numChunks_.z; k++) {
                std::vector<float> chunkData = extractChunkData(i, j, k, data);

                unsigned int chunkIdx = ArrayUtils::calculateIndex(i, j, k, numChunks_);
                chunks_[chunkIdx].setData(chunkData);
            }
        }
    }

    for (const auto& cb : observers_) {
        cb();
    }
}

const glm::vec3& ChunkManager::dims() const
{
    return numChunks_;
}

std::vector<float> ChunkManager::vertices(unsigned int x, unsigned int y, unsigned int z) const
{
    unsigned int chunkIdx = ArrayUtils::calculateIndex(x, y, z, numChunks_);
    auto chunk = chunks_[chunkIdx];
    return chunk.vertices(glm::vec3(x, y, z));
}

std::vector<float> ChunkManager::extractChunkData(
    unsigned int x, unsigned int y, unsigned int z, const std::vector<float>& data)
{
    unsigned int chunkIdx = ArrayUtils::calculateIndex(x, y, z, numChunks_);
    const auto& chunkDims = chunks_[chunkIdx].dims();

    unsigned int x0 = x * Voxel::CHUNK_SIZE;
    unsigned int y0 = y * Voxel::CHUNK_SIZE;
    unsigned int z0 = z * Voxel::CHUNK_SIZE;

    std::vector<float> chunkData(chunkDims.x * chunkDims.y * chunkDims.z);
    for (int i = 0; i < chunkDims.x; i++) {
        for (int j = 0; j < chunkDims.y; j++) {
            for (int k = 0; k < chunkDims.z; k++) {
                unsigned int blockIndex = ArrayUtils::calculateIndex(i, j, k, chunkDims);
                unsigned int dataIndex = ArrayUtils::calculateIndex(x0 + i, y0 + j, z0 + k, dims_);
                chunkData[blockIndex] = data[dataIndex];
            }
        }
    }

    return chunkData;
}
