#include "ChunkManager.h"

#include <glm/gtc/type_ptr.hpp>

#include <stdio.h>

// glm::vec3 calculateChunkDims(const glm::vec3& dims)
// {
//     unsigned int x = std::ceil(static_cast<float>(dims.x)/static_cast<float>(Voxel::CHUNK_SIZE));
//     unsigned int y = std::ceil(static_cast<float>(dims.y)/static_cast<float>(Voxel::CHUNK_SIZE));
//     unsigned int z = std::ceil(static_cast<float>(dims.z)/static_cast<float>(Voxel::CHUNK_SIZE));
//     return glm::vec3(x, y, z);
// }

ChunkManager::ChunkManager(const glm::vec3& dims)
{
    printf("[ChunkManager] gemerating %f %f %f\n", dims.x, dims.y, dims.z);

    // glm::vec3 chunkDims = calculateChunkDims(dims);
    chunkDims_ = glm::vec3(1, 1, 1);

    Chunk chunk;
    for(int k = 0; k < dims.z; k++) {
        for(int j = 0; j < dims.y; j++) {
            for(int i = 0; i < dims.x; i++) {
                chunk.enableBlock(i, j, k);
            }
        }
    }
    chunks_.push_back(chunk);

    updateMesh();
}

const std::vector<float>& ChunkManager::vertices() const
{
    return vertices_;
}

void ChunkManager::updateMesh()
{
    vertices_.clear();
    // TODO: reserve verts
    unsigned int n_yz = chunkDims_.y * chunkDims_.z;
    unsigned int n_y = chunkDims_.y;

    for(int k = 0; k < chunkDims_.z; k++) {
        for(int j = 0; j < chunkDims_.y; j++) {
            for(int i = 0; i < chunkDims_.x; i++) {
                unsigned int chunkIdx = (k * n_yz) + (j * n_y) + i;
                auto chunk = chunks_[chunkIdx];
                auto chunkVerts = chunk.vertices();
                vertices_.insert(vertices_.end(), chunkVerts.begin(), chunkVerts.end());
            }
        }
    }
}
