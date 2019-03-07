#pragma once

class IntegerId;
class I_Shader;

class I_ShaderBinder
{
public:
    virtual ~I_ShaderBinder() = default;

    virtual void clear() = 0;
    virtual bool bind(const IntegerId& shaderId) = 0;
    virtual I_Shader& boundShader() = 0;
};
