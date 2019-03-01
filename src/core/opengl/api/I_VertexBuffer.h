#pragma once

class I_VertexBuffer
{
public:
    virtual ~I_VertexBuffer() = default;

    virtual void bind() = 0;
    virtual void enable() = 0;
    virtual unsigned int count() = 0;
};
