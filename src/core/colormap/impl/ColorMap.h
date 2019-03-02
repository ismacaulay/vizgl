#pragma once
#include "I_ColorMap.h"

#include <vector>
#include <memory>

class ColorMap : public I_ColorMap
{
public:
    explicit ColorMap(const std::vector<unsigned char>& colors);
    ~ColorMap();

    void bind(unsigned int textureSlot);

private:
    class Impl;
    std::unique_ptr<Impl> p_;
};
