#pragma once
#include "IntegerId.h"
#include <memory>

template<typename T>
class I_Repository
{
public:
    virtual ~I_Repository() = default;

    virtual IntegerId insert(std::shared_ptr<T> value) = 0;
    virtual const T& lookup(const IntegerId& key) const = 0;
    virtual T& lookup(const IntegerId& key) = 0;

    virtual std::vector<std::reference_wrapper<T>> all() const = 0;
};
