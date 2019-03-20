#pragma once

#include "I_MappingFactory.h"

class I_ColorMap;
class I_IdLookupTable;
class I_VoxelEngine;
class IntegerId;
template<typename T> class I_Repository;

class MappingFactory : public I_MappingFactory
{
public:
    explicit MappingFactory(
        I_Repository<I_ColorMap>& colorMapRespository,
        I_IdLookupTable& geometryIdToVoxelIdLookupTable,
        I_VoxelEngine& voxelEngine);
    ~MappingFactory() = default;

    std::shared_ptr<I_Mapping> createStaticMapping(const glm::vec3& rgb);

    std::shared_ptr<I_Mapping> createContinuousMapping(
        const std::vector<float>& data,
        const IntegerId& colorMapId);

    std::shared_ptr<I_Mapping> createVoxelMapping(
        const std::vector<float>& data,
        const glm::vec3& rgb,
        const IntegerId& geometryId);
    std::shared_ptr<I_Mapping> createVoxelContinuousMapping(
        const std::vector<float>& data,
        const IntegerId& colorMapId,
        const IntegerId& geometryId);

private:
    I_Repository<I_ColorMap>& colorMapRespository_;
    I_IdLookupTable& geometryIdToVoxelIdLookupTable_;
    I_VoxelEngine& voxelEngine_;
};
