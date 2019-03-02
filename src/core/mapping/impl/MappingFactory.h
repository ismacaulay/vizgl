#pragma once

#include "I_MappingFactory.h"

template<typename T> class I_Repository;
class I_ColorMap;
class IntegerId;

class MappingFactory : public I_MappingFactory
{
public:
    explicit MappingFactory(I_Repository<I_ColorMap>& colorMapRespository);
    ~MappingFactory() = default;

    std::shared_ptr<I_Mapping> createStaticMapping(const glm::vec3& rgb);
    std::shared_ptr<I_Mapping> createContinuousMapping(
        const std::vector<float>& data,
        const IntegerId& colorMapId);

private:
    I_Repository<I_ColorMap>& colorMapRespository_;
};
