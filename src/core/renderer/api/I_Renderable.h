#pragma once

class Shader;
class ArrayBuffer;
class ArrayBufferLayout;

enum class RenderableType {
    Triangles,
};

class I_Renderable
{
public:
    virtual ~I_Renderable() = default;

    virtual const ArrayBuffer& vertexBuffer() const = 0;
    virtual const ArrayBufferLayout& vertexBufferLayout() const = 0;
    virtual Shader& shader() const = 0;
    virtual RenderableType type() const = 0;
    virtual unsigned int vertexCount() const = 0;
    virtual void bindUniforms() const = 0;
};
