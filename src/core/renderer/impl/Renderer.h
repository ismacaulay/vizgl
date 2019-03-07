#pragma once

template<typename T> class I_Repository;
class I_Camera;
class I_Model;
class I_ModelRenderer;
class I_Plot;
class I_ShaderBinder;

class Renderer
{
public:
    Renderer(
        const I_Camera& camera,
        const I_Plot& plot,
        I_ShaderBinder& shaderBinder,
        I_ModelRenderer& modelRenderer,
        const I_Repository<I_Model>& models);
    ~Renderer();

    void setSize(int width, int height);

    void render() const;

private:
    const I_Camera& camera_;
    const I_Plot& plot_;
    I_ShaderBinder& shaderBinder_;
    I_ModelRenderer& modelRenderer_;
    const I_Repository<I_Model>& models_;
};
