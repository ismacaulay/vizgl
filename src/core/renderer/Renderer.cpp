#include "Renderer.h"

#include <GLES2/gl2.h>
#include "GLError.h"

#include "I_Camera.h"
#include "I_Renderable.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Shader.h"

Renderer::Renderer(I_Camera& camera)
    : camera_(camera)
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

void Renderer::clear() const
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::render(const I_Renderable& renderable) const
{
    camera_.update();

    renderable.vertexArray().bind();
    renderable.vertexBuffer().bind();

    auto& shader = renderable.shader();
    shader.bind();
    shader.setUniformMat4f("u_model", glm::mat4(1.0f));
    shader.setUniformMat4f("u_view", camera_.view());
    shader.setUniformMat4f("u_proj", camera_.projection());

    GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 36));
}
