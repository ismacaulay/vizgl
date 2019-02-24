#pragma once

class Shader;
class VertexArray;
class VertexBuffer;

class I_Renderable
{
public:
    virtual ~I_Renderable() = default;

    virtual const VertexArray& vertexArray() const = 0;
    virtual const VertexBuffer& vertexBuffer() const = 0;
    virtual Shader& shader() const = 0;
};
