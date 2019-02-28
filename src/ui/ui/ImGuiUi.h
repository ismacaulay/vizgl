#pragma once

class I_ImGuiPresenter;

class ImGuiUi
{
public:
    explicit ImGuiUi(I_ImGuiPresenter& presenter);
    ~ImGuiUi() = default;

    void render();

private:
    bool open_ = true;
    float rotation_[3] = { 90.0f, 0.0f, 0.0f };
    I_ImGuiPresenter& presenter_;
};
