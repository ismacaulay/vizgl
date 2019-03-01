#include "ShaderManager.h"

#include "I_Repository.h"
#include "I_ShaderFactory.h"
#include "I_Mapping.h"

ShaderManager::ShaderManager(
    const I_Repository<I_Mapping>& mappingRepository,
    I_ShaderFactory& shaderFactory,
    I_Repository<I_Shader>& shaderRepository)
    :
      mappingRepository_(mappingRepository)
    , shaderFactory_(shaderFactory)
    , shaderRepository_(shaderRepository)
{
}

IntegerId ShaderManager::lookupShaderForMapping(const IntegerId& mappingId)
{
    const auto& mapping = mappingRepository_.lookup(mappingId);
    auto type = mapping.type();

    auto search = shaderMappingCache_.find(type);
    if (search != shaderMappingCache_.end()) {
        return search->second;
    }

    auto shader = shaderFactory_.createShaderForMappingType(type);
    auto shaderId = shaderRepository_.insert(shader);
    shaderMappingCache_.insert({ type, shaderId });

    return shaderId;
}
