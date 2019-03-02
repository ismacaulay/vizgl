#pragma once
#include "MappingType.h"

class I_Shader;
class IntegerId;

class I_Mapping
{
public:
    virtual ~I_Mapping() = default;

    virtual MappingType type() const = 0;
    virtual void bind(I_Shader& shader) = 0;

    virtual void setGradient(const IntegerId& gradient) = 0;
};
