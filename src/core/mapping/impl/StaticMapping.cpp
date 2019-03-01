#include "StaticMapping.h"

#include <stdio.h>
#include <GLES2/gl2.h>
#include "GLError.h"

StaticMapping::StaticMapping(const glm::vec3& rgb)
    : rgb_(rgb)
{
}

MappingType StaticMapping::type() const
{
    return MappingType::Static;
}

void StaticMapping::bind()
{
    int programId;
    GL_CALL(glGetIntegerv(GL_CURRENT_PROGRAM, &programId));

    int location;
    auto search = uniformLocationCache_.find(programId);
    if (search != uniformLocationCache_.end()) {
        location = search->second;
    } else {
        GL_CALL(location = glGetUniformLocation(programId, "u_color"));
        if (location == -1) {
            printf("Warning: Location for u_color does not exists in shader %d\n", programId);
            return;
        }
        uniformLocationCache_[programId] = location;
    }

    GL_CALL(glUniform3f(location, rgb_.r, rgb_.g, rgb_.b));
}
