#include "ModelRendererFactory.h"

#include "ModelRenderer.h"

ModelRendererFactory::ModelRendererFactory(
    I_Repository<I_Geometry>& geometryRepository,
    I_Repository<I_Shader>& shaderRepsitory,
    I_Repository<I_Mapping>& mappingRepository)
    :
      geometryRepository_(geometryRepository)
    , shaderRepsitory_(shaderRepsitory)
    , mappingRepository_(mappingRepository)
{
    (void)geometryRepository_;
    (void)shaderRepsitory_;
    (void)mappingRepository_;
}

std::shared_ptr<I_ModelRenderer> ModelRendererFactory::create(const I_Model& model)
{
    // return std::make_shared<ModelRenderer>(
    //     model, geometryRepository_, shaderRepsitory_, mappingRepository_);
    return nullptr;
}
