#include "Renderer.h"

#include <unordered_map>
#include <GLES2/gl2.h>
#include "GLError.h"

#include "I_Camera.h"
#include "I_Renderable.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "I_RenderableRepository.h"

namespace {
    const std::unordered_map<RenderableType, GLenum> typeToGlMap = {
        { RenderableType::Triangles, GL_TRIANGLES },
    };
}

Renderer::Renderer(I_Camera& camera, const I_RenderableRepository& respository)
    : camera_(camera)
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

    for (const I_Renderable* renderable : respository_.all())
    {
        renderable->vertexArray().bind();
        renderable->vertexBuffer().bind();

        auto& shader = renderable->shader();
        shader.bind();
        shader.setUniformMat4f("u_model", glm::mat4(1.0f));
        shader.setUniformMat4f("u_view", camera_.view());
        shader.setUniformMat4f("u_proj", camera_.projection());

        GL_CALL(glDrawArrays(typeToGlMap.at(renderable->type()), 0, renderable->vertexCount()));
    }
}
