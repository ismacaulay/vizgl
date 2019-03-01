#pragma once
#include "I_Repository.h"

#include "IntegerId.h"

template<typename T>
class GenericRepository : public I_Repository<T>
{
public:
    explicit GenericRepository();
    ~GenericRepository();

    IntegerId insert(std::shared_ptr<T> value);
    const T& lookup(const IntegerId& key) const;
    T& lookup(const IntegerId& key);

    std::vector<std::reference_wrapper<T>> all() const;

private:
    unsigned int nextId_;
    std::unordered_map<IntegerId, std::shared_ptr<T>> map_;
};

template<typename T>
GenericRepository<T>::GenericRepository()
    : nextId_(0)
{
}

template<typename T>
GenericRepository<T>::~GenericRepository()
{
    map_.clear();
}

template<typename T>
IntegerId GenericRepository<T>::insert(std::shared_ptr<T> value)
{
    IntegerId id(nextId_++);
    map_.insert({ id, value });
    return id;
}

template<typename T>
const T& GenericRepository<T>::lookup(const IntegerId& key) const
{
    return *(map_.at(key));
}

template<typename T>
T& GenericRepository<T>::lookup(const IntegerId& key)
{
    return *(map_.at(key));
}

template<typename T>
std::vector<std::reference_wrapper<T>> GenericRepository<T>::all() const
{
    std::vector<std::reference_wrapper<T>> values;
    for (auto& it : map_) {
        values.push_back(std::ref(*(it.second)));
    }
    return values;
}
