#include "ImGuiPresenter.h"

#include "ObservableValue.h"

ImGuiPresenter::ImGuiPresenter(ObservableValue<glm::vec3>& rotation)
    : rotation_(rotation)
{
}

void ImGuiPresenter::setRotation(float x, float y, float z)
{
    rotation_.setValue(glm::vec3(glm::radians(x), glm::radians(y), glm::radians(z)));
}
