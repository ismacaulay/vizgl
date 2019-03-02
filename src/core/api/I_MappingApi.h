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
};
