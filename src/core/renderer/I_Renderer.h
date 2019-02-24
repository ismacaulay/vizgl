#pragma once

class I_Renderable;

class I_Renderer
{
public:
    virtual ~I_Renderer() = default;

    virtual void clear() const = 0;
    virtual void render(const I_Renderable& renderable) const = 0;
};
