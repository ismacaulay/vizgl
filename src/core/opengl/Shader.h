#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

class Shader
{
public:
    Shader(const std::string& vertexShader, const std::string& fragmentShader);
    ~Shader();

    void bind() const;
    void unbind() const;

    void setUniform1f(const std::string& name, float v);
    void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
    void setUniform1i(const std::string& name, int v);
    void setUniformMat4f(const std::string& name, const glm::mat4& matrix);

private:
    unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
    unsigned int compileShader(unsigned int type, const std::string& source);

    int getUniformLocation(const std::string& name);

private:
    unsigned int id_;
    std::unordered_map<std::string, int> uniformLocationCache_;
};
