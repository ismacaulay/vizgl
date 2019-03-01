#pragma once

#include "I_MappingFactory.h"

class MappingFactory : public I_MappingFactory
{
public:
    explicit MappingFactory() = default;
    ~MappingFactory() = default;

    std::shared_ptr<I_Mapping> createStaticMapping(const glm::vec3& rgb);
};
