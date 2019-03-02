#pragma once
#include <vector>

#include "IntegerId.h"

class I_ColorMapApi
{
public:
    virtual ~I_ColorMapApi() = default;

    virtual IntegerId createColorMap(const std::vector<unsigned char>& colors) = 0;
};
