#pragma once

class I_Camera;
class I_RenderableRepository;

class Renderer
{
public:
    Renderer(I_Camera& camera, const I_RenderableRepository& respository);
    ~Renderer();

    void setSize(int width, int height);

    void render() const;

private:
    I_Camera& camera_;
    const I_RenderableRepository& respository_;
};
