#pragma once
#include <memory>

class I_Model;
class I_ModelRenderer;

class I_ModelRendererFactory
{
public:
    virtual ~I_ModelRendererFactory() = default;

    virtual std::shared_ptr<I_ModelRenderer> create(const I_Model& model) = 0;
};
