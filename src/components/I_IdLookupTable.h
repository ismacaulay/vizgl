#pragma once
#include "IntegerId.h"
#include <memory>

class I_IdLookupTable
{
public:
    virtual ~I_IdLookupTable() = default;

    virtual void insert(const IntegerId& key, const IntegerId& value) = 0;
    virtual const IntegerId& lookup(const IntegerId& key) const = 0;
};
