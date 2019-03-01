#include "MappingManager.h"

#include "I_MappingFactory.h"
#include "I_Repository.h"

MappingManager::MappingManager(I_MappingFactory& factory, I_Repository<I_Mapping>& repository)
    : factory_(factory)
    , repository_(repository)
{
}

IntegerId MappingManager::createStaticMapping(const glm::vec3& rgb)
{
    auto mapping = factory_.createStaticMapping(rgb);
    return repository_.insert(mapping);
}
