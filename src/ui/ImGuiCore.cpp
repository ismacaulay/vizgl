#include "ImGuiCore.h"

#include <glm/glm.hpp>

#include "Core.h"
#include "ImGuiPresenter.h"
#include "ImGuiUi.h"
#include "ObservableValue.h"
#include "PlotController.h"

class ImGuiCore::Impl
{
public:
    Impl(const Core& core)
        : plotEntity(glm::vec3(0.0f, 0.0f, 0.0f))

        , plotController(core.plotApi(), plotEntity)

        , presenter(plotEntity)
        , ui(presenter)
    {
    }

    void render()
    {
        ui.render();
    }

    ObservableValue<glm::vec3> plotEntity;

    PlotController plotController;

    ImGuiPresenter presenter;
    ImGuiUi ui;
};

ImGuiCore::ImGuiCore(const Core& core)
    : p_(std::make_unique<Impl>(core))
{
}
ImGuiCore::~ImGuiCore()
{
}

void ImGuiCore::render()
{
    p_->render();
}
