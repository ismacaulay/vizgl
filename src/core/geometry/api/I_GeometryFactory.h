#pragma once
#include <memory>
#include <vector>

class I_Geometry;

class I_GeometryFactory
{
public:
    virtual ~I_GeometryFactory() = default;

    virtual std::shared_ptr<I_Geometry> createMesh(const std::vector<float>& vertices) = 0;
};
