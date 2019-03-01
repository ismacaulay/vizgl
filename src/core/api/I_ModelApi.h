#pragma once
#include "IntegerId.h"

class I_ModelApi
{
public:
    virtual ~I_ModelApi() = default;

    virtual IntegerId createModel(
        const IntegerId& geometryId,
        const IntegerId& mappingId) = 0;
};
