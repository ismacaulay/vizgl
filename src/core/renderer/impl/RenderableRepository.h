#pragma once
#include "I_RenderableRepository.h"

class RenderableRepository : public I_RenderableRepository
{
public:
    explicit RenderableRepository();
    virtual ~RenderableRepository();

    void add(const I_Renderable* renderable);
    const std::vector<const I_Renderable*>& all() const;

private:
    std::vector<const I_Renderable*> storage_;
};
