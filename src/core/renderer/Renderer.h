#pragma once
#include "I_Renderer.h"

class I_Camera;
class I_Renderable;

class Renderer : public I_Renderer
{
public:
    Renderer(I_Camera& camera);
    ~Renderer();

    void setSize(int width, int height);

    void clear() const;
    void render(const I_Renderable& renderable) const;

private:
    I_Camera& camera_;
};
