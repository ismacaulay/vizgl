#pragma once
#include "I_VoxelEngine.h"

template<typename T> class I_Repository;
class I_ChunkManager;
class I_ChunkManagerFactory;

class VoxelEngine : public I_VoxelEngine
{
public:
    explicit VoxelEngine(
        I_ChunkManagerFactory& chunkManagerFactory,
        I_Repository<I_ChunkManager>& chunkManagerRepository);
    ~VoxelEngine() = default;

    IntegerId generate(const glm::vec3& dims);

    const std::vector<float>& vertices(const IntegerId& mesh) const;

private:
    I_ChunkManagerFactory& chunkManagerFactory_;
    I_Repository<I_ChunkManager>& chunkManagerRepository_;
};
