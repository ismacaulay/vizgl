#pragma once
#include <glm/glm.hpp>

class I_ModelRenderer
{
public:
    virtual ~I_ModelRenderer() = default;

    virtual void render(const glm::mat4& model, const glm::mat4& view, const glm::mat4& proj) = 0;
};
