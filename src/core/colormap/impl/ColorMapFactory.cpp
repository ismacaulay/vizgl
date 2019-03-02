#include "ColorMapFactory.h"

#include "ColorMap.h"

std::shared_ptr<I_ColorMap> ColorMapFactory::createColorMap(const std::vector<unsigned char>& colors)
{
    return std::make_shared<ColorMap>(colors);
}
