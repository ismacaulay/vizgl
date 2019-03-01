#pragma once
#include <glm/glm.hpp>

#include "IntegerId.h"

class I_MappingApi
{
public:
    virtual ~I_MappingApi() = default;

    virtual IntegerId createStaticMapping(const glm::vec3& rgb) = 0;
};
