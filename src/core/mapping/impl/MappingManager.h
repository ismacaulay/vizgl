#pragma once
#include "I_MappingApi.h"

class I_MappingFactory;
template<typename T> class I_Repository;
class I_Mapping;

class MappingManager : public I_MappingApi
{
public:
    explicit MappingManager(I_MappingFactory& factory, I_Repository<I_Mapping>& repository);
    ~MappingManager() = default;

    IntegerId createStaticMapping(const glm::vec3& rgb);

private:
    I_MappingFactory& factory_;
    I_Repository<I_Mapping>& repository_;
};
