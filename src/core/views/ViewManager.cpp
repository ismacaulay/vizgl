#include "ViewManager.h"

#include "I_RenderableRepository.h"
#include "I_View.h"
#include "I_ViewFactory.h"

ViewManager::ViewManager(I_ViewFactory& factory, I_RenderableRepository& repository)
    : factory_(factory)
    , repository_(repository)
{
}

void ViewManager::createMesh(const std::vector<float>& vertices)
{
    const auto* view = factory_.createMesh(vertices);
    repository_.add(view);
}

void ViewManager::createMesh(const std::vector<float>& vertices, const std::vector<uint32_t>& indices)
{
}
