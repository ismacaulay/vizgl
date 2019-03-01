#include "MappingFactory.h"

#include "StaticMapping.h"

std::shared_ptr<I_Mapping> MappingFactory::createStaticMapping(const glm::vec3& rgb)
{
    return std::make_shared<StaticMapping>(rgb);
}
