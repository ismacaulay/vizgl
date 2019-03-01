#include "GeometryManager.h"

#include "I_GeometryFactory.h"
#include "I_Repository.h"

GeometryManager::GeometryManager(I_GeometryFactory& factory, I_Repository<I_Geometry>& repository)
    : factory_(factory)
    , repository_(repository)
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
