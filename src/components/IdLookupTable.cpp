#include "IdLookupTable.h"

void IdLookupTable::insert(const IntegerId& key, const IntegerId& value)
{
    lookupTable_.insert({ key, value });
}

const IntegerId& IdLookupTable::lookup(const IntegerId& key) const
{
    return lookupTable_.at(key);
}
