#include "IntegerId.h"
#include <limits>

namespace
{
    const unsigned int NULL_ID = std::numeric_limits<unsigned int>::max();
}

IntegerId::IntegerId()
    : value_(NULL_ID)
{
}

IntegerId::IntegerId(unsigned int value)
    : value_(value)
{
}

unsigned int IntegerId::value() const
{
    return value_;
}

bool IntegerId::isNull() const
{
    return value_ == NULL_ID;
}

bool IntegerId::operator==(const IntegerId& other) const
{
    return value_ == other.value();
}
