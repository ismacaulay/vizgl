#pragma once

#include "I_GeometryFactory.h"

class GeometryFactory : public I_GeometryFactory
{
public:
    explicit GeometryFactory() = default;
    ~GeometryFactory() = default;

    std::shared_ptr<I_Geometry> createMesh(const std::vector<float>& vertices);
};
