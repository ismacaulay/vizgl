#pragma once
#include "I_VoxelGeometry.h"

#include <memory>

class I_VoxelEngine;
class IntegerId;

class VoxelGeometry : public I_VoxelGeometry
{
public:
    explicit VoxelGeometry(const IntegerId& id, I_VoxelEngine& engine);
    ~VoxelGeometry();

    GeometryType type() const;
    const BoundingBox& boundingBox() const;
    unsigned int vertexCount() const;

    void render(I_Shader& shader);

    const IntegerId& voxelMeshId() const;

private:
    class Impl;
    std::unique_ptr<Impl> p_;
};
