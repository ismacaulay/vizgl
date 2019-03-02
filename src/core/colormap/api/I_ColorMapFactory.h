#pragma once
#include <memory>
#include <vector>

class I_ColorMap;

class I_ColorMapFactory
{
public:
    virtual ~I_ColorMapFactory() = default;

    virtual std::shared_ptr<I_ColorMap> createColorMap(const std::vector<unsigned char>& colors) = 0;
};
