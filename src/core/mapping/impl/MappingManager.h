#pragma once
#include "I_MappingApi.h"

template<typename T> class I_Repository;
class I_DataToGeometryMapper;
class I_Mapping;
class I_MappingFactory;

class MappingManager : public I_MappingApi
{
public:
    explicit MappingManager(
        I_MappingFactory& factory,
        I_Repository<I_Mapping>& repository);
    ~MappingManager() = default;

    IntegerId createStaticMapping(const glm::vec3& rgb);

    IntegerId createContinuousMapping(
        const std::vector<float>& data, const IntegerId& colorMapId);
    void setContinuousMappingGradient(
        const IntegerId& mappingId, const IntegerId& colorMapId);

    IntegerId createVoxelMapping(
        const std::vector<float>& data,
        const glm::vec3& rgb,
        const IntegerId& geometryId);
    IntegerId createVoxelContinuousMapping(
        const std::vector<float>& data,
        const IntegerId& colorMapId,
        const IntegerId& geometryId);

private:
    I_MappingFactory& factory_;
    I_Repository<I_Mapping>& repository_;
};
