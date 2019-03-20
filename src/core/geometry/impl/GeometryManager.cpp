#include "GeometryManager.h"

#include "I_GeometryFactory.h"
#include "I_IdLookupTable.h"
#include "I_Repository.h"
#include "I_VoxelGeometry.h"

#include <stdio.h>

GeometryManager::GeometryManager(
    I_GeometryFactory& factory,
    I_Repository<I_Geometry>& repository,
    I_IdLookupTable& geometryToVoxelMeshLookupTable)
    : factory_(factory)
    , repository_(repository)
    , geometryToVoxelMeshLookupTable_(geometryToVoxelMeshLookupTable)
{
}

IntegerId GeometryManager::createMesh(const std::vector<float>& vertices)
{
    auto geometry = factory_.createMesh(vertices);
    return repository_.insert(geometry);
}

IntegerId GeometryManager::createMesh(
    const std::vector<float>& vertices,
    const std::vector<uint32_t>& triangles)
{
    std::vector<float> positions(triangles.size() * 3);
    for(int i = 0; i < triangles.size(); i++) {
        auto index = triangles[i];
        positions[(i * 3) + 0] = vertices[(index * 3) + 0];
        positions[(i * 3) + 1] = vertices[(index * 3) + 1];
        positions[(i * 3) + 2] = vertices[(index * 3) + 2];
    }

    return createMesh(positions);
}

IntegerId GeometryManager::createVoxelMesh(const glm::vec3& dims)
{
    auto geometry = factory_.createVoxelMesh(dims);
    auto geometryId = repository_.insert(geometry);
    geometryToVoxelMeshLookupTable_.insert(geometryId, geometry->voxelMeshId());
    return geometryId;
}

IntegerId GeometryManager::createVoxelMesh(const std::vector<float>& tensor_u,
                                           const std::vector<float>& tensor_v,
                                           const std::vector<float>& tensor_w)
{
    auto geometry = factory_.createVoxelMesh(tensor_u, tensor_v, tensor_w);
    auto geometryId = repository_.insert(geometry);
    geometryToVoxelMeshLookupTable_.insert(geometryId, geometry->voxelMeshId());
    return geometryId;
}
