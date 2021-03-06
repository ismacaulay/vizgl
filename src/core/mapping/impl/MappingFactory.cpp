#include "MappingFactory.h"

#include "ContinuousMapping.h"
#include "I_IdLookupTable.h"
#include "I_VoxelEngine.h"
#include "StaticMapping.h"
#include "VoxelContinuousMapping.h"

MappingFactory::MappingFactory(
    I_Repository<I_ColorMap>& colorMapRespository,
    I_IdLookupTable& geometryIdToVoxelIdLookupTable,
    I_VoxelEngine& voxelEngine)
    : colorMapRespository_(colorMapRespository)
    , geometryIdToVoxelIdLookupTable_(geometryIdToVoxelIdLookupTable)
    , voxelEngine_(voxelEngine)
{
}

std::shared_ptr<I_Mapping> MappingFactory::createStaticMapping(const glm::vec3& rgb)
{
    return std::make_shared<StaticMapping>(rgb, false);
}

std::shared_ptr<I_Mapping> MappingFactory::createContinuousMapping(
    const std::vector<float>& data,
    const IntegerId& colorMapId)
{
    return std::make_shared<ContinuousMapping>(data, colorMapRespository_, colorMapId, false);
}

std::shared_ptr<I_Mapping> MappingFactory::createVoxelMapping(
    const std::vector<float>& data,
    const glm::vec3& rgb,
    const IntegerId& geometryId)
{
    auto voxelId = geometryIdToVoxelIdLookupTable_.lookup(geometryId);
    voxelEngine_.setData(voxelId, data);

    return std::make_shared<StaticMapping>(rgb, true);
}

std::shared_ptr<I_Mapping> MappingFactory::createVoxelContinuousMapping(
    const std::vector<float>& data,
    const IntegerId& colorMapId,
    const IntegerId& geometryId)
{
    auto voxelId = geometryIdToVoxelIdLookupTable_.lookup(geometryId);
    voxelEngine_.setData(voxelId, data);

    return std::make_shared<VoxelContinuousMapping>(data, colorMapRespository_, colorMapId, true);
}
