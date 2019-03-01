#pragma once
#include "I_ModelRendererFactory.h"

template<typename T> class I_Repository;
class I_Geometry;
class I_Mapping;
class I_Shader;

class ModelRendererFactory: public I_ModelRendererFactory
{
public:
    explicit ModelRendererFactory(
        I_Repository<I_Geometry>& geometryRepository,
        I_Repository<I_Shader>& shaderRepsitory,
        I_Repository<I_Mapping>& mappingRepository);
    ~ModelRendererFactory() = default;

    std::shared_ptr<I_ModelRenderer> create(const I_Model& model);

private:
    I_Repository<I_Geometry>& geometryRepository_;
    I_Repository<I_Shader>& shaderRepsitory_;
    I_Repository<I_Mapping>& mappingRepository_;
};
