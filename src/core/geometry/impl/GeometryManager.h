#pragma once
#include "I_GeometryApi.h"

class I_Geometry;
class I_GeometryFactory;
class I_IdLookupTable;
template<typename T> class I_Repository;

class GeometryManager : public I_GeometryApi
{
public:
    explicit GeometryManager(
        I_GeometryFactory& factory,
        I_Repository<I_Geometry>& repository,
        I_IdLookupTable& geometryToVoxelMeshLookupTable);
    ~GeometryManager() = default;

    IntegerId createMesh(const std::vector<float>& vertices);
    IntegerId createMesh(const std::vector<float>& vertices,
                         const std::vector<uint32_t>& triangles);

    IntegerId createBlockModel(const glm::vec3& dims);

private:
    I_GeometryFactory& factory_;
    I_Repository<I_Geometry>& repository_;
    I_IdLookupTable& geometryToVoxelMeshLookupTable_;
};
