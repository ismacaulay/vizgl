#include "ChunkManager.h"

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
    printf("[ChunkManager] generating %f %f %f\n", dims.x, dims.y, dims.z);

    dims_ = calculateNumberOfChunks(dims);
    printf("[ChunkManager] dims_: %f %f %f\n", dims_.x, dims_.y, dims_.z);
    for(int k = 0; k < dims_.z; k++) {
        for(int j = 0; j < dims_.y; j++) {
            for(int i = 0; i < dims_.x; i++) {
                glm::vec3 chunkDims = calculateChunkDims(i, j, k, dims);
                Chunk chunk = createChunk(chunkDims);
                chunks_.push_back(chunk);
            }
        }
    }

    // updateMesh();
}

void ChunkManager::onChanged(const std::function<void()>& cb)
{
    observers_.push_back(cb);
}

void ChunkManager::setData(const std::vector<float>& data)
{
}

const glm::vec3& ChunkManager::dims() const
{
    return dims_;
}

const std::vector<float>& ChunkManager::vertices() const
{
    return vertices_;
}

std::vector<float> ChunkManager::vertices(unsigned int x, unsigned int y, unsigned int z) const
{
    unsigned int chunkIdx = (z * dims_.x * dims_.y) + (y * dims_.x) + x;
    auto chunk = chunks_[chunkIdx];
    return chunk.vertices(glm::vec3(x, y, z));
}

Chunk ChunkManager::createChunk(const glm::vec3& dims)
{
    Chunk chunk;
    for(int k = 0; k < dims.z; k++) {
        for(int j = 0; j < dims.y; j++) {
            for(int i = 0; i < dims.x; i++) {
                chunk.enableBlock(i, j, k);
            }
        }
    }
    return chunk;
}

void ChunkManager::updateMesh()
{
    vertices_.clear();
    // TODO: reserve verts
    for(int k = 0; k < dims_.z; k++) {
        for(int j = 0; j < dims_.y; j++) {
            for(int i = 0; i < dims_.x; i++) {
                unsigned int chunkIdx = (k * dims_.x * dims_.y) + (j * dims_.x) + i;
                auto chunk = chunks_[chunkIdx];
                auto chunkVerts = chunk.vertices(glm::vec3(i, j, k));
                vertices_.insert(vertices_.end(), chunkVerts.begin(), chunkVerts.end());
            }
        }
    }
}
