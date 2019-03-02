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

private:
    I_MappingFactory& factory_;
    I_Repository<I_Mapping>& repository_;
};
