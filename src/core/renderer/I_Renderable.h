#pragma once

class Shader;
class VertexBuffer;
class VertexBufferLayout;

enum class RenderableType {
    Triangles,
};

class I_Renderable
{
public:
    virtual ~I_Renderable() = default;

    virtual const VertexBuffer& vertexBuffer() const = 0;
    virtual const VertexBufferLayout& vertexBufferLayout() const = 0;
    virtual Shader& shader() const = 0;
    virtual RenderableType type() const = 0;
    virtual unsigned int vertexCount() const = 0;
};
