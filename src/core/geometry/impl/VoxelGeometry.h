#pragma once
#include "I_Geometry.h"

#include <memory>

class I_VoxelEngine;
class IntegerId;

class VoxelGeometry : public I_Geometry
{
public:
    explicit VoxelGeometry(const IntegerId& id, I_VoxelEngine& engine);
    ~VoxelGeometry();

    GeometryType type() const;
    const BoundingBox& boundingBox() const;
    unsigned int vertexCount() const;

    void bind(I_Shader& shader);

private:
    class Impl;
    std::unique_ptr<Impl> p_;
};
