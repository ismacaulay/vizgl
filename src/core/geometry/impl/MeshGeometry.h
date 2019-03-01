#pragma once
#include "I_Geometry.h"

#include <memory>
#include <vector>

class MeshGeometry : public I_Geometry
{
public:
    explicit MeshGeometry(const std::vector<float>& vertices);
    ~MeshGeometry();

    GeometryType type() const;
    const BoundingBox& boundingBox() const;
    unsigned int vertexCount() const;

    void bind();


private:
    class Impl;
    std::unique_ptr<Impl> p_;
};
