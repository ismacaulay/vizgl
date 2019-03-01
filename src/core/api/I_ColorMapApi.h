#pragma once
#include <vector>
#include <glm/glm.hpp>

#include "IntegerId.h"

class I_ColorMapApi
{
public:
    virtual ~I_ColorMapApi() = default;

    virtual IntegerId createColorMap(const std::vector<glm::vec3>& colors) = 0;
};
