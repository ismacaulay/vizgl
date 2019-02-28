#pragma once
#include "I_View.h"

#include <glm/glm.hpp>
#include <memory>
#include <vector>

class MeshView : public I_View
{
public:
    MeshView(const std::vector<float>& vertices, const glm::vec4& color);
    virtual ~MeshView() = default;

    const VertexBuffer& vertexBuffer() const;
    const VertexBufferLayout& vertexBufferLayout() const;
    Shader& shader() const;
    RenderableType type() const;
    unsigned int vertexCount() const;
    void bindUniforms() const;

private:
    class Impl;
    std::unique_ptr<Impl> p_;
};
