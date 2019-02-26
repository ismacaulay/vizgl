#include "Renderer.h"

#include "GLError.h"
#include <GLES2/gl2.h>
#include <unordered_map>

#include "I_Camera.h"
#include "I_Plot.h"
#include "I_Renderable.h"
#include "I_RenderableRepository.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace {
    const std::unordered_map<RenderableType, GLenum> typeToGlMap = {
        { RenderableType::Triangles, GL_TRIANGLES },
    };
}

Renderer::Renderer(
    const I_Camera& camera,
    const I_Plot& plot,
    const I_RenderableRepository& respository)
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

    for (const I_Renderable* renderable : respository_.all())
    {
        renderable->vertexBuffer().bind();
        unsigned int offset = 0;
        const auto& layout = renderable->vertexBufferLayout();
        const auto& elements = layout.getElements();
        for (auto i = 0ul; i < elements.size(); i++) {
            const auto& element = elements[i];
            GL_CALL(glEnableVertexAttribArray(i));
            GL_CALL(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset));
            offset += element.count * VertexBufferElement::getSizeOfType(element.type);
        }

        auto& shader = renderable->shader();
        shader.bind();
        shader.setUniformMat4f("u_model", plot_.model());
        shader.setUniformMat4f("u_view", camera_.view());
        shader.setUniformMat4f("u_proj", camera_.projection());

        GL_CALL(glDrawArrays(typeToGlMap.at(renderable->type()), 0, renderable->vertexCount()));
    }
}
