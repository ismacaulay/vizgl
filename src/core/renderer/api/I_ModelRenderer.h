#pragma once

class I_Model;
class I_Shader;

class I_ModelRenderer
{
public:
    virtual ~I_ModelRenderer() = default;

    virtual void render(const I_Model& model, I_Shader& shader) = 0;
};
