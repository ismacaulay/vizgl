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
    };
}

ModelRenderer::ModelRenderer(
    const I_Model& model,
    I_Repository<I_Geometry>& geometryRepository,
    I_Repository<I_Shader>& shaderRepsitory,
    I_Repository<I_Mapping>& mappingsRepository)
    : model_(model)
    , geometryRepository_(geometryRepository)
    , shaderRepsitory_(shaderRepsitory)
    , mappingsRepository_(mappingsRepository)
{
}

void ModelRenderer::render(const glm::mat4& model, const glm::mat4& view, const glm::mat4& proj)
{
    auto& geometry = geometryRepository_.lookup(model_.geometryId());
    auto& shader = shaderRepsitory_.lookup(model_.shaderId());
    auto& mapping = mappingsRepository_.lookup(model_.mappingId());

    geometry.bind();

    shader.bind();
    shader.setUniformMat4f("u_model", model);
    shader.setUniformMat4f("u_view", view);
    shader.setUniformMat4f("u_proj", proj);

    mapping.bind();

    GL_CALL(glDrawArrays(typeToGlMap.at(geometry.type()), 0, geometry.vertexCount()));
}
