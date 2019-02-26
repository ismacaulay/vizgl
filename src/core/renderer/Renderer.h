#pragma once

class I_Camera;
class I_Plot;
class I_RenderableRepository;

class Renderer
{
public:
    Renderer(
        const I_Camera& camera,
        const I_Plot& plot,
        const I_RenderableRepository& respository);
    ~Renderer();

    void setSize(int width, int height);

    void render() const;

private:
    const I_Camera& camera_;
    const I_Plot& plot_;
    const I_RenderableRepository& respository_;
};
