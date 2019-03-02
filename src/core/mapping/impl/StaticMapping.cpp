#include "StaticMapping.h"

#include <GLES2/gl2.h>
#include "GLError.h"

#include "I_Shader.h"

StaticMapping::StaticMapping(const glm::vec3& rgb)
    : rgb_(rgb)
{
}

MappingType StaticMapping::type() const
{
    return MappingType::Static;
}

void StaticMapping::bind(I_Shader& shader)
{
    shader.bind();

    auto normalizeColor = [](const glm::vec3& color) {
        return glm::vec3(
            static_cast<float>(color.r) / 255.0f,
            static_cast<float>(color.g) / 255.0f,
            static_cast<float>(color.b) / 255.0f
        );
    };
    glm::vec3 normalizedColor = normalizeColor(rgb_);
    shader.setUniform3f("u_color", normalizedColor.r, normalizedColor.g, normalizedColor.b);
}
