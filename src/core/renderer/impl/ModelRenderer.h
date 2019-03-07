#pragma once
#include "I_ModelRenderer.h"

class I_Model;
template<typename T> class I_Repository;
class I_Geometry;
class I_Shader;
class I_Mapping;

class ModelRenderer : public I_ModelRenderer
{
public:
    explicit ModelRenderer(
        I_Repository<I_Geometry>& geometryRepository,
        I_Repository<I_Mapping>& mappingRepository);
    ~ModelRenderer() = default;

    void render(const I_Model& model, I_Shader& shader);

private:
    I_Repository<I_Geometry>& geometryRepository_;
    I_Repository<I_Mapping>& mappingsRepository_;
};
