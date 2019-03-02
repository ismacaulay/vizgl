#include "ColorMapManager.h"

#include "I_ColorMapFactory.h"
#include "I_Repository.h"

ColorMapManager::ColorMapManager(I_ColorMapFactory& factory, I_Repository<I_ColorMap>& repository)
    : factory_(factory)
    , repository_(repository)
{
}

IntegerId ColorMapManager::createColorMap(const std::vector<unsigned char>& colors)
{
    auto colormap = factory_.createColorMap(colors);
    return repository_.insert(colormap);
}
