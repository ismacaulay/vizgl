#pragma once
#include "IntegerId.h"

class I_ShaderManager
{
public:
    virtual ~I_ShaderManager() = default;

    virtual IntegerId lookupShaderForMapping(const IntegerId& mappingId) = 0;
};
