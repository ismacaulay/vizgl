#pragma once
#include "I_ShaderFactory.h"

class ShaderFactory : public I_ShaderFactory
{
public:
    explicit ShaderFactory() = default;
    ~ShaderFactory() = default;

    std::shared_ptr<I_Shader> createShaderForMappingType(MappingType type);
};
