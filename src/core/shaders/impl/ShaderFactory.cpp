#include "ShaderFactory.h"

#include "ContinuousMappingShaderSource.h"
#include "Shader.h"
#include "StaticShaderSource.h"

std::shared_ptr<I_Shader> ShaderFactory::createShaderForMappingType(MappingType type)
{
    switch (type)
    {
        case MappingType::Static:
        {
            return std::make_shared<Shader>(
                StaticShaderSource::VertexShader,
                StaticShaderSource::FragmentShader);
        }
        case MappingType::StaticWithWireframe:
        {
            return std::make_shared<Shader>(
                StaticShaderSource::VertexShaderWithWireframe,
                StaticShaderSource::FragmentShaderWithWireframe);
        }
        case MappingType::Continuous:
        {
            return std::make_shared<Shader>(
                ContinuousMappingShaderSource::VertexShader,
                ContinuousMappingShaderSource::FragmentShader);
        }
    };

    return nullptr;
}
