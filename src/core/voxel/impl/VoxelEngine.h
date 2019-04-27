#pragma once
#include "I_VoxelEngine.h"

template<typename T> class I_Repository;

class VoxelEngine : public I_VoxelEngine
{
public:
    explicit VoxelEngine(I_Repository<bme::Mesh>& repository);
    ~VoxelEngine() = default;

    IntegerId generate(const glm::uvec3& dims);

    void onChanged(const IntegerId& mesh, const std::function<void()>& cb);
    void setData(const IntegerId& mesh, const std::vector<float>& data);

    const bme::Mesh& mesh(const IntegerId& id) const;

private:
    I_Repository<bme::Mesh>& repository_;
};
