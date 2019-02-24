#pragma once

class I_Renderer;
class I_ViewRepository;

class ViewRenderer
{
public:
    ViewRenderer(const I_Renderer& renderer, const I_ViewRepository& repository);
    ~ViewRenderer() = default;

    void render();

private:
    const I_Renderer& renderer_;
    const I_ViewRepository& repository_;
};
