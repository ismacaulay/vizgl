#include "StaticMapping.h"

#include <GLES2/gl2.h>
#include "GLError.h"

#include "I_Shader.h"

StaticMapping::StaticMapping(const glm::vec3& rgb, bool wireframe)
    :  normalizedColor_(
        static_cast<float>(rgb.r) / 255.0f,
        static_cast<float>(rgb.g) / 255.0f,
        static_cast<float>(rgb.b) / 255.0f)
    , wireframe_(wireframe)
{
}

MappingType StaticMapping::type() const
{
    return wireframe_ ? MappingType::StaticWithWireframe : MappingType::Static;
}

void StaticMapping::bind(I_Shader& shader)
{
    shader.setUniform3f("u_color", normalizedColor_.r, normalizedColor_.g, normalizedColor_.b);
}

void StaticMapping::setGradient(const IntegerId& gradient)
{
}
