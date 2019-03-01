#pragma once
#include "I_ColorMap.h"

#include <vector>
#include <glm/glm.hpp>

class ColorMap : public I_ColorMap
{
public:
    explicit ColorMap(const std::vector<glm::vec3>& colors);
    ~ColorMap() = default;
};
