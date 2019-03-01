#pragma once
#include "I_ShaderManager.h"
#include "MappingType.h"

template<typename T> class I_Repository;
class I_ShaderFactory;
class I_Mapping;
class I_Shader;

class ShaderManager : public I_ShaderManager
{
public:
    explicit ShaderManager(
        const I_Repository<I_Mapping>& mappingRepository,
        I_ShaderFactory& shaderFactory,
        I_Repository<I_Shader>& shaderRepository);
    ~ShaderManager() = default;

    IntegerId lookupShaderForMapping(const IntegerId& mappingId);

private:
    const I_Repository<I_Mapping>& mappingRepository_;
    I_ShaderFactory& shaderFactory_;
    I_Repository<I_Shader>& shaderRepository_;

    std::unordered_map<MappingType, IntegerId> shaderMappingCache_;
};
