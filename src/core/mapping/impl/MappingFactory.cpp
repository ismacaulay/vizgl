#include "MappingFactory.h"

#include "ContinuousMapping.h"
#include "StaticMapping.h"

MappingFactory::MappingFactory(I_Repository<I_ColorMap>& colorMapRespository)
    : colorMapRespository_(colorMapRespository)
{
}

std::shared_ptr<I_Mapping> MappingFactory::createStaticMapping(const glm::vec3& rgb)
{
    return std::make_shared<StaticMapping>(rgb);
}

std::shared_ptr<I_Mapping> MappingFactory::createContinuousMapping(
    const std::vector<float>& data,
    const IntegerId& colorMapId)
{
    return std::make_shared<ContinuousMapping>(data, colorMapRespository_, colorMapId);
}
