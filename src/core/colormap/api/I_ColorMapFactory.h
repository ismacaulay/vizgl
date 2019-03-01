#pragma once
#include <memory>
#include <vector>
#include <glm/glm.hpp>

class I_ColorMap;

class I_ColorMapFactory
{
public:
    virtual ~I_ColorMapFactory() = default;

    virtual std::shared_ptr<I_ColorMap> createColorMap(const std::vector<glm::vec3>& colors) = 0;
};
