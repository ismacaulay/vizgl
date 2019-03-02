#include "Texture.h"

#include <GLES2/gl2.h>
#include "GLError.h"

Texture::Texture(
    const std::vector<unsigned char>& data,
    unsigned int width,
    unsigned int height)
    : textureId_(0)
{
    GL_CALL(glGenTextures(1, &textureId_));
    GL_CALL(glBindTexture(GL_TEXTURE_2D, textureId_));

    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data.data()));
}

Texture::~Texture() {
    GL_CALL(glDeleteTextures(1, &textureId_));
}

void Texture::bind(unsigned int slot) const {
    GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
    GL_CALL(glBindTexture(GL_TEXTURE_2D, textureId_));
}

void Texture::unbind() const {
    GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
}
