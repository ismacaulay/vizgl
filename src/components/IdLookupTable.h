#pragma once
#include "I_IdLookupTable.h"

class IdLookupTable : public I_IdLookupTable
{
public:
    explicit IdLookupTable() = default;
    ~IdLookupTable() = default;

    void insert(const IntegerId& key, const IntegerId& value);
    const IntegerId& lookup(const IntegerId& key) const;

private:
    std::unordered_map<IntegerId, IntegerId> lookupTable_;
};
