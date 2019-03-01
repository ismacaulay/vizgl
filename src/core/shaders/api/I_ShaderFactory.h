#pragma once
#include <memory>
#include "MappingType.h"

class I_Shader;

class I_ShaderFactory
{
public:
    virtual ~I_ShaderFactory() = default;

    virtual std::shared_ptr<I_Shader> createShaderForMappingType(MappingType type) = 0;
};
