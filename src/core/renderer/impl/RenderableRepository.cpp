#include "RenderableRepository.h"

#include "I_Renderable.h"

RenderableRepository::RenderableRepository()
{
}
RenderableRepository::~RenderableRepository()
{
    for (const I_Renderable* v : storage_) {
        delete v;
    }
}

void RenderableRepository::add(const I_Renderable* renderable)
{
    storage_.push_back(renderable);
}

const std::vector<const I_Renderable*>& RenderableRepository::all() const
{
    return storage_;
}
