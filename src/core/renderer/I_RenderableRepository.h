#pragma once

#include <vector>

class I_Renderable;

class I_RenderableRepository
{
public:
    virtual ~I_RenderableRepository() = default;

    virtual void add(const I_Renderable* redenerable) = 0;
    virtual const std::vector<const I_Renderable*>& all() const = 0;
};
