#pragma once

#include <vector>

class Texture {
public:
    Texture(
        const std::vector<unsigned char>& data,
        unsigned int width,
        unsigned int height);
    ~Texture();

    void bind(unsigned int slot = 0) const;
    void unbind() const;

private:
    unsigned int textureId_;
};
