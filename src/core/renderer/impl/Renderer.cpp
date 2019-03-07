#include "Renderer.h"

#include "GLError.h"
#include <GLES2/gl2.h>

#include "I_Camera.h"
#include "I_Plot.h"
#include "I_ModelRenderer.h"
#include "I_Repository.h"
#include "I_ShaderBinder.h"
#include "I_Shader.h"
#include "I_Model.h"

Renderer::Renderer(
    const I_Camera& camera,
    const I_Plot& plot,
    I_ShaderBinder& shaderBinder,
    I_ModelRenderer& modelRenderer,
    const I_Repository<I_Model>& models)
    : camera_(camera)
    , plot_(plot)
    , shaderBinder_(shaderBinder)
    , modelRenderer_(modelRenderer)
    , models_(models)
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

    shaderBinder_.clear();
    for (auto& model : models_.all()) {

        if (shaderBinder_.bind(model.get().shaderId())) {
            auto& shader = shaderBinder_.boundShader();
            shader.setUniformMat4f("u_model", plot_.model());
            shader.setUniformMat4f("u_view", camera_.view());
            shader.setUniformMat4f("u_proj", camera_.projection());
        }

        modelRenderer_.render(model.get(), shaderBinder_.boundShader());
    }
}
