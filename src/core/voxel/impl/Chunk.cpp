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

std::vector<float> Chunk::vertices(const glm::vec3& chunkIndex) const
{
    std::vector<float> verts;
    // const auto addTriangle = [&verts](const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2) {
    const auto addFace = [&verts](glm::vec3 t1[3], glm::vec3 t2[3]) {
        // triangle 1
        glm::vec3 p0 = t1[0];
        glm::vec3 p1 = t1[1];
        glm::vec3 p2 = t1[2];

        verts.push_back(p0.x); verts.push_back(p0.y); verts.push_back(p0.z);
        verts.push_back(1.0); verts.push_back(1.0); verts.push_back(0.0);

        verts.push_back(p1.x); verts.push_back(p1.y); verts.push_back(p1.z);
        verts.push_back(1.0); verts.push_back(0.0); verts.push_back(0.0);

        verts.push_back(p2.x); verts.push_back(p2.y); verts.push_back(p2.z);
        verts.push_back(1.0); verts.push_back(0.0); verts.push_back(1.0);

        // triangle 2
        p0 = t2[0];
        p1 = t2[1];
        p2 = t2[2];

        verts.push_back(p0.x); verts.push_back(p0.y); verts.push_back(p0.z);
        verts.push_back(1.0); verts.push_back(1.0); verts.push_back(0.0);

        verts.push_back(p1.x); verts.push_back(p1.y); verts.push_back(p1.z);
        verts.push_back(1.0); verts.push_back(0.0); verts.push_back(0.0);

        verts.push_back(p2.x); verts.push_back(p2.y); verts.push_back(p2.z);
        verts.push_back(1.0); verts.push_back(0.0); verts.push_back(1.0);
    };

    glm::vec3 baseOffset = chunkIndex * static_cast<float>(Voxel::CHUNK_SIZE);
    for(int k = 0; k < Voxel::CHUNK_SIZE; k++) {
        for(int j = 0; j < Voxel::CHUNK_SIZE; j++) {
            for(int i = 0; i < Voxel::CHUNK_SIZE; i++) {
                unsigned int index = blockIndex(i, j, k);
                const auto& block = blocks_[index];
                if (block.isActive()) {
                    glm::vec3 offset = baseOffset + glm::vec3(i, j, k);
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
                        glm::vec3 t1[3] = { p0, p1, p2 };
                        glm::vec3 t2[3] = { p2, p3, p0 };
                        addFace(t1, t2);
                    }

                    bool addBackFace = true;
                    if (k < Voxel::CHUNK_SIZE - 1) {
                        addBackFace = !blocks_[blockIndex(i, j, k+1)].isActive();
                    }
                    if (addBackFace) {
                        glm::vec3 t1[3] = {p5, p4, p7};
                        glm::vec3 t2[3] = {p7, p6, p5};
                        addFace(t1, t2);
                    }

                    bool addLeftFace = true;
                    if (i > 0) {
                        addLeftFace = !blocks_[blockIndex(i-1, j, k)].isActive();
                    }
                    if(addLeftFace) {
                        glm::vec3 t1[3] = {p4, p0, p3};
                        glm::vec3 t2[3] = {p3, p7, p4};
                        addFace(t1, t2);
                    }

                    bool addRightFace = true;
                    if (i < Voxel::CHUNK_SIZE - 1) {
                        addRightFace = !blocks_[blockIndex(i+1, j, k)].isActive();
                    }
                    if(addRightFace) {
                        glm::vec3 t1[3] = {p1, p5, p6};
                        glm::vec3 t2[3] = {p6, p2, p1};
                        addFace(t1, t2);
                    }

                    bool addTopFace = true;
                    if (j < Voxel::CHUNK_SIZE - 1) {
                        addTopFace = !blocks_[blockIndex(i, j+1, k)].isActive();
                    }
                    if(addTopFace) {
                        glm::vec3 t1[3] = {p3, p2, p6};
                        glm::vec3 t2[3] = {p6, p7, p3};
                        addFace(t1, t2);
                    }

                    bool addBottomFace = true;
                    if (j > 0) {
                        addBottomFace = !blocks_[blockIndex(i, j-1, k)].isActive();
                    }
                    if (addBottomFace) {
                        glm::vec3 t1[3] = {p0, p4, p5};
                        glm::vec3 t2[3] = {p5, p1, p0};
                        addFace(t1, t2);
                    }
                }
            }
        }
    }

    return verts;
}

unsigned int Chunk::blockIndex(unsigned int x, unsigned int y, unsigned int z) const
{
    return (z * Voxel::CHUNK_SIZE * Voxel::CHUNK_SIZE) + (y * Voxel::CHUNK_SIZE) + x;
}
