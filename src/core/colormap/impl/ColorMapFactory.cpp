#include "ColorMapFactory.h"

#include "ColorMap.h"

std::shared_ptr<I_ColorMap> ColorMapFactory::createColorMap(const std::vector<glm::vec3>& colors)
{
    return std::make_shared<ColorMap>(colors);
}
