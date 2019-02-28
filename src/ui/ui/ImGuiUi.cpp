#include "ImGuiUi.h"

#include <imgui/imgui.h>

#include "I_ImGuiPresenter.h"

ImGuiUi::ImGuiUi(I_ImGuiPresenter& presenter)
    : presenter_(presenter)
{
}

void ImGuiUi::render()
{
    if (!ImGui::Begin("Controls", &open_, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::End();
        return;
    };

    ImGui::Text("Average FPS: %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    ImGui::Separator();

    if (ImGui::CollapsingHeader("Plot controls"))
    {
        ImGui::SliderFloat3("rotation", rotation_, -90.0f, 90.0f);
        presenter_.setRotation(rotation_[0], rotation_[1], rotation_[2]);
    }

    ImGui::End();
}
