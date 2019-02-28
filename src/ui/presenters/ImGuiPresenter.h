#pragma once
#include "I_ImGuiPresenter.h"

#include <glm/glm.hpp>

template<typename T>
class ObservableValue;

class ImGuiPresenter : public I_ImGuiPresenter
{
public:
    explicit ImGuiPresenter(ObservableValue<glm::vec3>& rotation);
    ~ImGuiPresenter() = default;

    void setRotation(float x, float y, float z);

private:
    ObservableValue<glm::vec3>& rotation_;
};
