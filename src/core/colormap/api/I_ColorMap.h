#pragma once

class I_ColorMap
{
public:
    virtual ~I_ColorMap() = default;

    virtual void bind(unsigned int textureSlot) = 0;
};
