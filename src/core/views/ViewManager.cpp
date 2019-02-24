#include "ViewManager.h"

#include "I_ViewFactory.h"
#include "I_ViewRepository.h"

ViewManager::ViewManager(I_ViewFactory& factory, I_ViewRepository& repository)
    : factory_(factory)
    , repository_(repository)
{
}

void ViewManager::createMesh(const std::vector<float>& vertices)
{
    auto view = factory_.createMesh(vertices);
    repository_.addView(view);
}
