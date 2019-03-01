#include "ModelManager.h"

#include "I_Geometry.h"
#include "I_ModelFactory.h"
#include "I_ModelRendererFactory.h"
#include "I_Plot.h"
#include "I_Repository.h"
#include "I_ShaderManager.h"

ModelManager::ModelManager(
    I_ModelFactory& modelFactory,
    I_Repository<I_Model>& modelRepository,
    I_ShaderManager& shaderManager,
    I_ModelRendererFactory& modelRendererFactory,
    I_Repository<I_ModelRenderer>& rendererRepository,
    I_Plot& plot,
    I_Repository<I_Geometry>& geometryRepository)
    :
      modelFactory_(modelFactory)
    , modelRepository_(modelRepository)
    , shaderManager_(shaderManager)
    , modelRendererFactory_(modelRendererFactory)
    , rendererRepository_(rendererRepository)
    , plot_(plot)
    , geometryRepository_(geometryRepository)
{
}

IntegerId ModelManager::createModel(const IntegerId& geometryId, const IntegerId& mappingId)
{
    auto& geometry = geometryRepository_.lookup(geometryId);
    plot_.contain(geometry.boundingBox());

    auto shaderId = shaderManager_.lookupShaderForMapping(mappingId);

    auto model = modelFactory_.create(geometryId, shaderId, mappingId);
    auto modelId = modelRepository_.insert(model);

    auto renderer = modelRendererFactory_.create(*model);
    rendererRepository_.insert(renderer);

    return modelId;
}
