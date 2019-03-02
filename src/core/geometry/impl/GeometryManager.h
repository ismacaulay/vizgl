#pragma once
#include "I_GeometryApi.h"

class I_GeometryFactory;
template<typename T> class I_Repository;
class I_Geometry;

class GeometryManager : public I_GeometryApi
{
public:
    explicit GeometryManager(I_GeometryFactory& factory, I_Repository<I_Geometry>& repository);
    ~GeometryManager() = default;

    IntegerId createMesh(const std::vector<float>& vertices);
    IntegerId createMesh(const std::vector<float>& vertices,
                         const std::vector<uint32_t>& triangles);

private:
    I_GeometryFactory& factory_;
    I_Repository<I_Geometry>& repository_;
};
