#include "Shader.h"

#include <string>
#include <glm/gtc/type_ptr.hpp>
#include <GLES2/gl2.h>
#include "GLError.h"

Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader)
    : id_(createShader(vertexShader, fragmentShader))
{
}
Shader::~Shader()
{
    GL_CALL(glDeleteProgram(id_));
}

void Shader::bind() const
{
    GL_CALL(glUseProgram(id_));
}

void Shader::unbind() const
{
    GL_CALL(glUseProgram(0));
}

void Shader::setUniform1f(const std::string& name, float v)
{
    GL_CALL(glUniform1f(getUniformLocation(name), v));
}

void Shader::setUniform3f(const std::string& name, float v0, float v1, float v2)
{
    GL_CALL(glUniform3f(getUniformLocation(name), v0, v1, v2));
}

void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    GL_CALL(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}

void Shader::setUniform1i(const std::string& name, int v)
{
    GL_CALL(glUniform1i(getUniformLocation(name), v));
}

void Shader::setUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
    GL_CALL(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix)));
}

void Shader::enableAttribute(const std::string& name)
{
    int location = getAttributeLocation(name);
    GL_CALL(glEnableVertexAttribArray(location));
}

void Shader::vertexAttributePointer(
    const std::string& name,
    unsigned int size,
    unsigned int type,
    bool normalized,
    unsigned int stride,
    unsigned int offset)
{
    int location = getAttributeLocation(name);
    GL_CALL(glVertexAttribPointer(location, size, type, normalized, stride, (void *)offset));
}

unsigned int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    GL_CALL(unsigned int program = glCreateProgram());
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GL_CALL(glAttachShader(program, vs));
    GL_CALL(glAttachShader(program, fs));
    GL_CALL(glLinkProgram(program));
    GL_CALL(glValidateProgram(program));

    GL_CALL(glDeleteShader(vs));
    GL_CALL(glDeleteShader(fs));

    return program;
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source)
{
    GL_CALL(unsigned int id = glCreateShader(type));
    const char* src = source.c_str();
    GL_CALL(glShaderSource(id, 1, &src, nullptr));
    GL_CALL(glCompileShader(id));

    int result;
    GL_CALL(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE) {
        int length;
        GL_CALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = static_cast<char*>(alloca(length * sizeof(char)));
        GL_CALL(glGetShaderInfoLog(id, length, &length, message));

        printf("Failed to compile %s\n", (type == GL_VERTEX_SHADER ? "vertex" : "fragment"));
        printf("%s\n", message);
        GL_CALL(glDeleteShader(id));
        return 0;
    }

    return id;
}

int Shader::getUniformLocation(const std::string& name)
{
    auto search = uniformLocationCache_.find(name);
    if (search != uniformLocationCache_.end()) {
        return search->second;
    }

    GL_CALL(int location = glGetUniformLocation(id_, name.c_str()));
    if (location == -1) {
        printf("Warning: Location for %s does not exists in shader %d\n", name.c_str(), id_);
    }
    uniformLocationCache_[name] = location;
    return location;
}

int Shader::getAttributeLocation(const std::string& name)
{
    auto search = attributeLocationCache_.find(name);
    if (search != attributeLocationCache_.end()) {
        return search->second;
    }

    GL_CALL(int location = glGetAttribLocation(id_, name.c_str()));
    if (location == -1) {
        printf("Warning: Location for %s does not exists in shader %d\n", name.c_str(), id_);
    }
    attributeLocationCache_[name] = location;
    return location;
}
