#pragma once

template<typename T> class I_Repository;
class I_Camera;
class I_Plot;
class I_ModelRenderer;

class Renderer
{
public:
    Renderer(
        const I_Camera& camera,
        const I_Plot& plot,
        const I_Repository<I_ModelRenderer>& respository);
    ~Renderer();

    void setSize(int width, int height);

    void render() const;

private:
    const I_Camera& camera_;
    const I_Plot& plot_;
    const I_Repository<I_ModelRenderer>& respository_;
};
