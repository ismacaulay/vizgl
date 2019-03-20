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
        return std::min(Voxel::CHUNK_SIZE, dim - (index * Voxel::CHUNK_SIZE));
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

ChunkManager::ChunkManager(const std::vector<float>& tensor_u,
                           const std::vector<float>& tensor_v,
                           const std::vector<float>& tensor_w)
{
    dims_ = glm::vec3(tensor_u.size(), tensor_v.size(), tensor_w.size());
    numChunks_ = calculateNumberOfChunks(dims_);
    printf("[ChunkManager] num chunks: %f %f %f\n", numChunks_.x,  numChunks_.y,  numChunks_.z);
    for (int i = 0; i < numChunks_.x; i++) {
        unsigned int x0 = i * Voxel::CHUNK_SIZE;
        for (int j = 0; j < numChunks_.y; j++) {
            unsigned int y0 = j * Voxel::CHUNK_SIZE;
            for (int k = 0; k < numChunks_.z; k++) {
                unsigned int z0 = k * Voxel::CHUNK_SIZE;

                glm::vec3 chunkDims = calculateChunkDims(i, j, k, dims_);
                std::vector<float> chunkTensorU(tensor_u.begin() + x0, tensor_u.begin() + x0 + chunkDims.x);
                std::vector<float> chunkTensorV(tensor_v.begin() + y0, tensor_v.begin() + y0 + chunkDims.y);
                std::vector<float> chunkTensorW(tensor_w.begin() + z0, tensor_w.begin() + z0 + chunkDims.z);

                Chunk chunk(chunkDims);
                chunk.setSizes(chunkTensorU, chunkTensorV, chunkTensorW);
                chunks_.push_back(chunk);
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
    float xOffset = 0.0;
    for(int i = 0; i < x; i++) {
        unsigned int chunkIdx = ArrayUtils::calculateIndex(i, 0, 0, numChunks_);
        const auto& chunkSize = chunks_[chunkIdx].size();
        xOffset += chunkSize.x;
    }

    float yOffset = 0.0;
    for(int i = 0; i < y; i++) {
        unsigned int chunkIdx = ArrayUtils::calculateIndex(0, i, 0, numChunks_);
        const auto& chunkSize = chunks_[chunkIdx].size();
        yOffset += chunkSize.y;
    }

    float zOffset = 0.0;
    for(int i = 0; i < z; i++) {
        unsigned int chunkIdx = ArrayUtils::calculateIndex(0, 0, i, numChunks_);
        const auto& chunkSize = chunks_[chunkIdx].size();
        zOffset += chunkSize.z;
    }

    unsigned int chunkIdx = ArrayUtils::calculateIndex(x, y, z, numChunks_);
    auto chunk = chunks_[chunkIdx];
    glm::vec3 offset(xOffset, yOffset, zOffset);
    return chunk.vertices(offset);
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
