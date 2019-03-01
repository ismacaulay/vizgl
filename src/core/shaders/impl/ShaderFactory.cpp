#include "ShaderFactory.h"

#include "StaticShaderSource.h"
#include "Shader.h"

std::shared_ptr<I_Shader> ShaderFactory::createShaderForMappingType(MappingType type)
{
    switch (type)
    {
        case MappingType::Static:
        {
            return std::make_shared<Shader>(StaticShaderSource::VertexShader, StaticShaderSource::FragmentShader);
        }
    };

    return nullptr;
}
