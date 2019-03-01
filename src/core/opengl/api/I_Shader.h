#pragma once

#include <string>
#include <glm/glm.hpp>

class I_Shader
{
public:
    virtual ~I_Shader() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual void setUniform1f(const std::string& name, float v) = 0;
    virtual void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) = 0;
    virtual void setUniform1i(const std::string& name, int v) = 0;
    virtual void setUniformMat4f(const std::string& name, const glm::mat4& matrix) = 0;
};
