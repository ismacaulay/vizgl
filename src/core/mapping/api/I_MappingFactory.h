#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <vector>

class I_Mapping;
class IntegerId;

class I_MappingFactory
{
public:
    virtual ~I_MappingFactory() = default;

    virtual std::shared_ptr<I_Mapping> createStaticMapping(const glm::vec3& rgb) = 0;

    virtual std::shared_ptr<I_Mapping> createContinuousMapping(
        const std::vector<float>& data,
        const IntegerId& colorMapId) = 0;

    virtual std::shared_ptr<I_Mapping> createVoxelMapping(
        const std::vector<float>& data,
        const glm::vec3& rgb,
        const IntegerId& geometryId) = 0;
    virtual std::shared_ptr<I_Mapping> createVoxelContinuousMapping(
        const std::vector<float>& data,
        const IntegerId& colorMapId,
        const IntegerId& geometryId) = 0;
};
