#pragma once
#include <memory>
#include <glm/glm.hpp>

class I_Mapping;

class I_MappingFactory
{
public:
    virtual ~I_MappingFactory() = default;

    virtual std::shared_ptr<I_Mapping> createStaticMapping(const glm::vec3& rgb) = 0;
};
