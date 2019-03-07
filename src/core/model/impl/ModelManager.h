#pragma once
#include "I_ModelApi.h"

template<typename T> class I_Repository;
class I_Geometry;
class I_Model;
class I_ModelFactory;
class I_ModelRenderer;
class I_ModelRendererFactory;
class I_Plot;
class I_ShaderManager;

class ModelManager : public I_ModelApi
{
public:
    explicit ModelManager(
        I_ModelFactory& modelFactory,
        I_Repository<I_Model>& modelRepository,
        I_ShaderManager& shaderManager,
        I_Plot& plot,
        I_Repository<I_Geometry>& geometryRepository);
    ~ModelManager() = default;

    IntegerId createModel(const IntegerId& geometryId, const IntegerId& mappingId);

private:
    I_ModelFactory& modelFactory_;
    I_Repository<I_Model>& modelRepository_;
    I_ShaderManager& shaderManager_;
    I_Plot& plot_;
    I_Repository<I_Geometry>& geometryRepository_;
};
