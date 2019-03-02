#include "ColorMap.h"

#include "Texture.h"

class ColorMap::Impl
{
public:
    Impl(const std::vector<unsigned char>& colors)
        : texture(colors, colors.size() / 3, 1)
    {
    }

    void bind(unsigned int slot)
    {
        texture.bind(slot);
    }

    Texture texture;
};

ColorMap::ColorMap(const std::vector<unsigned char>& colors)
    : p_(std::make_unique<Impl>(colors))
{
}
ColorMap::~ColorMap()
{
}

void ColorMap::bind(unsigned int textureSlot)
{
    p_->bind(textureSlot);
}
