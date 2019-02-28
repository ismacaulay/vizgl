#pragma once

class I_ImGuiPresenter
{
public:
    virtual ~I_ImGuiPresenter() = default;

    virtual void setRotation(float x, float y, float z) = 0;
};
