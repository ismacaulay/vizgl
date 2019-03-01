#include "Renderer.h"

#include "GLError.h"
#include <GLES2/gl2.h>

#include "I_Camera.h"
#include "I_Plot.h"
#include "I_ModelRenderer.h"
#include "I_Repository.h"

Renderer::Renderer(
    const I_Camera& camera,
    const I_Plot& plot,
    const I_Repository<I_ModelRenderer>& respository)
    : camera_(camera)
    , plot_(plot)
    , respository_(respository)
{
    GL_CALL(glEnable(GL_BLEND));
    GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GL_CALL(glEnable(GL_DEPTH_TEST));
}
Renderer::~Renderer()
{
}

void Renderer::setSize(int width, int height)
{
    glViewport(0, 0, width, height);
}

void Renderer::render() const
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (const auto& renderer : respository_.all())
    {
        renderer.get().render(plot_.model(), camera_.view(), camera_.projection());
    }
}
