#pragma once

#include "I_ColorMapFactory.h"

class I_View;

class ColorMapFactory : public I_ColorMapFactory
{
public:
    explicit ColorMapFactory() = default;
    ~ColorMapFactory() = default;

    std::shared_ptr<I_ColorMap> createColorMap(const std::vector<unsigned char>& colors);
};
