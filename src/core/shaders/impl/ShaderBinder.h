#pragma once
#include "I_ShaderBinder.h"

#include "IntegerId.h"

template<typename T> class I_Repository;
class I_Shader;

class ShaderBinder : public I_ShaderBinder
{
public:
    explicit ShaderBinder(I_Repository<I_Shader>& shaders);
    ~ShaderBinder() = default;

    void clear();
    bool bind(const IntegerId& shaderId);
    I_Shader& boundShader();

private:
    I_Repository<I_Shader>& shaders_;
    IntegerId boundShaderId_;
};
