#include "MappingManager.h"

#include "I_MappingFactory.h"
#include "I_Repository.h"
#include "I_Mapping.h"

MappingManager::MappingManager(
    I_MappingFactory& factory,
    I_Repository<I_Mapping>& repository)
    : factory_(factory)
    , repository_(repository)
{
}

IntegerId MappingManager::createStaticMapping(const glm::vec3& rgb)
{
    auto mapping = factory_.createStaticMapping(rgb);
    return repository_.insert(mapping);
}


IntegerId MappingManager::createContinuousMapping(
    const std::vector<float>& data, const IntegerId& colorMapId)
{
    auto mapping = factory_.createContinuousMapping(data, colorMapId);
    return repository_.insert(mapping);
}

void MappingManager::setContinuousMappingGradient(
    const IntegerId& mappingId, const IntegerId& colorMapId)
{
    auto& mapping = repository_.lookup(mappingId);
    mapping.setGradient(colorMapId);
}

IntegerId MappingManager::createVoxelMapping(
    const std::vector<float>& data, const glm::vec3& rgb, const IntegerId& geometryId)
{
    auto mapping = factory_.createVoxelMapping(data, rgb, geometryId);
    return repository_.insert(mapping);
}

IntegerId MappingManager::createVoxelContinuousMapping(
    const std::vector<float>& data, const IntegerId& colorMapId, const IntegerId& geometryId)
{
    auto mapping = factory_.createVoxelContinuousMapping(data, colorMapId, geometryId);
    return repository_.insert(mapping);
}
