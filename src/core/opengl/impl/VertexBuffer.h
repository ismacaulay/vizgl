#pragma once

class VertexBuffer {
public:
    explicit VertexBuffer();
    explicit VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void setData(const void* data, unsigned int size);

    void bind() const;
    void unbind() const;

private:
    unsigned int rendererID_;
};
