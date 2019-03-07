#include "ShaderBinder.h"

#include "I_Repository.h"
#include "I_Shader.h"

ShaderBinder::ShaderBinder(I_Repository<I_Shader>& shaders)
    : shaders_(shaders)
{
    clear();
}

void ShaderBinder::clear()
{
    boundShaderId_ = IntegerId::null();
}

bool ShaderBinder::bind(const IntegerId& shaderId)
{
    if (shaderId != boundShaderId_) {
        boundShaderId_ = shaderId;
        boundShader().bind();
        return true;
    }

    return false;
}

I_Shader& ShaderBinder::boundShader()
{
    return shaders_.lookup(boundShaderId_);
}
