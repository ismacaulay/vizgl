#pragma once
#include "IntegerId.h"
#include <vector>

class I_GeometryApi
{
public:
    virtual ~I_GeometryApi() = default;

    virtual IntegerId createMesh(const std::vector<float>& vertices) = 0;
    virtual IntegerId createMesh(const std::vector<float>& vertices,
                                 const std::vector<uint32_t>& triangles) = 0;
};
