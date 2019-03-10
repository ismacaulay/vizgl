#include "Chunk.h"

#include "VoxelDefines.h"

Chunk::Chunk()
{
    const unsigned int totalBlocks = Voxel::CHUNK_SIZE * Voxel::CHUNK_SIZE * Voxel::CHUNK_SIZE;
    blocks_.reserve(totalBlocks);
    for(int i = 0; i < totalBlocks; i++) {
        blocks_.emplace_back();
    }
}

void Chunk::enableBlock(unsigned int x, unsigned int y, unsigned int z)
{
    unsigned int index = blockIndex(x, y, z);
    blocks_[index].setActive(true);
}

std::vector<float> Chunk::vertices() const
{
    int currentColor = 0;
    std::vector<glm::vec3> colors = {
        { 1.0, 0.0, 0.0 },
        { 0.0, 1.0, 0.0 },
        { 0.0, 0.0, 1.0 },
    };

    std::vector<float> verts;
    const auto addVert = [&verts, &colors, &currentColor](const glm::vec3& vert) {
        verts.push_back(vert.x);
        verts.push_back(vert.y);
        verts.push_back(vert.z);

        auto color = colors[currentColor];
        verts.push_back(color.x);
        verts.push_back(color.y);
        verts.push_back(color.z);
    };

    for(int k = 0; k < Voxel::CHUNK_SIZE; k++) {
        for(int j = 0; j < Voxel::CHUNK_SIZE; j++) {
            for(int i = 0; i < Voxel::CHUNK_SIZE; i++) {
                unsigned int index = blockIndex(i, j, k);
                const auto& block = blocks_[index];
                if (block.isActive()) {
                    glm::vec3 offset(i, j, k);
                    glm::vec3 p0 = block.getVertex(0, offset);
                    glm::vec3 p1 = block.getVertex(1, offset);
                    glm::vec3 p2 = block.getVertex(2, offset);
                    glm::vec3 p3 = block.getVertex(3, offset);
                    glm::vec3 p4 = block.getVertex(4, offset);
                    glm::vec3 p5 = block.getVertex(5, offset);
                    glm::vec3 p6 = block.getVertex(6, offset);
                    glm::vec3 p7 = block.getVertex(7, offset);

                    bool addFrontFace = true;
                    if (k > 0) {
                        addFrontFace = !blocks_[blockIndex(i, j, k-1)].isActive();
                    }
                    if(addFrontFace) {
                        addVert(p0); addVert(p1); addVert(p2);
                        addVert(p2); addVert(p3); addVert(p0);
                    }

                    bool addBackFace = true;
                    if (k < Voxel::CHUNK_SIZE - 1) {
                        addBackFace = !blocks_[blockIndex(i, j, k+1)].isActive();
                    }
                    if (addBackFace) {
                        addVert(p5); addVert(p4); addVert(p7);
                        addVert(p7); addVert(p6); addVert(p5);
                    }

                    bool addLeftFace = true;
                    if (i > 0) {
                        addLeftFace = !blocks_[blockIndex(i-1, j, k)].isActive();
                    }
                    if(addLeftFace) {
                        addVert(p4); addVert(p0); addVert(p3);
                        addVert(p3); addVert(p7); addVert(p4);
                    }

                    bool addRightFace = true;
                    if (i < Voxel::CHUNK_SIZE - 1) {
                        addRightFace = !blocks_[blockIndex(i+1, j, k)].isActive();
                    }
                    if(addRightFace) {
                        addVert(p1); addVert(p5); addVert(p6);
                        addVert(p6); addVert(p2); addVert(p1);
                    }

                    bool addTopFace = true;
                    if (j < Voxel::CHUNK_SIZE - 1) {
                        addTopFace = !blocks_[blockIndex(i, j+1, k)].isActive();
                    }
                    if(addTopFace) {
                        addVert(p3); addVert(p2); addVert(p6);
                        addVert(p6); addVert(p7); addVert(p3);
                    }

                    bool addBottomFace = true;
                    if (j > 0) {
                        addBottomFace = !blocks_[blockIndex(i, j-1, k)].isActive();
                    }
                    if (addBottomFace) {
                        addVert(p0); addVert(p4); addVert(p5);
                        addVert(p5); addVert(p1); addVert(p0);
                    }
                }

                currentColor = (currentColor + 1) % 3;
            }
        }
    }

    return verts;
}

unsigned int Chunk::blockIndex(unsigned int x, unsigned int y, unsigned int z) const
{
    return (z * Voxel::CHUNK_SIZE * Voxel::CHUNK_SIZE) + (y * Voxel::CHUNK_SIZE) + x;
}
