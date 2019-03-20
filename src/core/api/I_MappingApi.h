#pragma once
#include <glm/glm.hpp>
#include <vector>

#include "IntegerId.h"

class I_MappingApi
{
public:
    virtual ~I_MappingApi() = default;

    virtual IntegerId createStaticMapping(const glm::vec3& rgb) = 0;

    virtual IntegerId createContinuousMapping(
        const std::vector<float>& data, const IntegerId& colorMapId) = 0;
    virtual void setContinuousMappingGradient(
        const IntegerId& mappingId, const IntegerId& colorMapId) = 0;

    virtual IntegerId createVoxelMapping(
        const std::vector<float>& data, const glm::vec3& rgb, const IntegerId& geometryId) = 0;
    virtual IntegerId createVoxelContinuousMapping(
        const std::vector<float>& data,
        const IntegerId& colorMapId,
        const IntegerId& geometryId) = 0;
};
