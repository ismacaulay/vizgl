#include "VertexArray.h"

#include <GLES2/gl2.h>
#include "GLError.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray() {
}

VertexArray::~VertexArray() {
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
    bind();
    vb.bind();

    unsigned int offset = 0;
    const auto& elements = layout.getElements();
    for (auto i = 0ul; i < elements.size(); i++) {
        const auto& element = elements[i];
        GL_CALL(glEnableVertexAttribArray(i));
        GL_CALL(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset));
        offset += element.count * VertexBufferElement::getSizeOfType(element.type);
    }
}

void VertexArray::bind() const {
}

void VertexArray::unbind() const {
}
