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

    void onChanged(const IntegerId& mesh, const std::function<void()>& cb);
    void setData(const IntegerId& mesh, const std::vector<float>& data);

    const glm::vec3& dims(const IntegerId& mesh) const;
    const std::vector<float>& vertices(const IntegerId& mesh) const;
    std::vector<float> vertices(const IntegerId& mesh, unsigned int x, unsigned int y, unsigned int z) const;


private:
    I_ChunkManagerFactory& chunkManagerFactory_;
    I_Repository<I_ChunkManager>& chunkManagerRepository_;
};
