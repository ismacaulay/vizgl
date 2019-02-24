#include "ViewRenderer.h"

#include "I_Renderer.h"
#include "I_View.h"
#include "I_ViewRepository.h"

ViewRenderer::ViewRenderer(const I_Renderer& renderer, const I_ViewRepository& repository)
    : renderer_(renderer)
    , repository_(repository)
{
}

void ViewRenderer::render()
{
    renderer_.clear();

    auto allViews = repository_.allViews();
    for (const auto* view : allViews)
    {
        renderer_.render(*view);
    }
}
