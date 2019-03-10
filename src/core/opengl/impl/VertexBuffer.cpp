#include "VertexBuffer.h"

#include <GLES2/gl2.h>
#include "GLError.h"

#include <stdio.h>

VertexBuffer::VertexBuffer()
{
    GL_CALL(glGenBuffers(1, &rendererID_));
}

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    GL_CALL(glGenBuffers(1, &rendererID_));
    setData(data, size);
}

VertexBuffer::~VertexBuffer()
{
    printf("[VertexBuffer] delete: %d\n", rendererID_);
    GL_CALL(glDeleteBuffers(1, &rendererID_));
}

void VertexBuffer::setData(const void* data, unsigned int size)
{
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, rendererID_));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

void VertexBuffer::bind() const
{
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, rendererID_));
}

void VertexBuffer::unbind() const
{
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
