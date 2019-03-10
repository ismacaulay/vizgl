#include "ModelRenderer.h"

#include <GLES2/gl2.h>
#include "GLError.h"

#include "I_Model.h"
#include "I_Repository.h"
#include "I_Geometry.h"
#include "I_Shader.h"
#include "I_Mapping.h"

namespace {
    const std::unordered_map<GeometryType, GLenum> typeToGlMap = {
        { GeometryType::Mesh, GL_TRIANGLES },
        { GeometryType::Voxel, GL_TRIANGLES },
    };
}

ModelRenderer::ModelRenderer(
    I_Repository<I_Geometry>& geometryRepository,
    I_Repository<I_Mapping>& mappingsRepository)
    : geometryRepository_(geometryRepository)
    , mappingsRepository_(mappingsRepository)
{
}

void ModelRenderer::render(const I_Model& model, I_Shader& shader)
{
    auto& geometry = geometryRepository_.lookup(model.geometryId());
    auto& mapping = mappingsRepository_.lookup(model.mappingId());

    mapping.bind(shader);
    geometry.render(shader);
    // GL_CALL(glDrawArrays(typeToGlMap.at(geometry.type()), 0, geometry.vertexCount()));
}
