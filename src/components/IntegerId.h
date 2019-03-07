#pragma once
#include <unordered_map>

class IntegerId
{
public:
    explicit IntegerId();
    explicit IntegerId(unsigned int value);
    ~IntegerId() = default;

    unsigned int value() const;
    bool isNull() const;

    bool operator==(const IntegerId& other) const;
    bool operator!=(const IntegerId& other) const;

    static IntegerId null();

private:
    unsigned int value_;
};

namespace std {
    template <>
    struct hash<IntegerId>
    {
        std::size_t operator()(const IntegerId& id) const
        {
            return std::hash<unsigned int>{}(id.value());
        }
    };
}
