#include "ContinuousMapping.h"

#include <algorithm>
#include <GLES2/gl2.h>
#include "GLError.h"

#include "I_ColorMap.h"
#include "I_Repository.h"
#include "I_Shader.h"
#include "VertexBuffer.h"

class ContinuousMapping::Impl
{
public:
    Impl(
        const std::vector<float>& data,
        I_Repository<I_ColorMap>& colorMapRepository,
        const IntegerId& gradientId)
        :
          vb(data.data(), data.size() * sizeof(float))
        , colorMapRepository(colorMapRepository)
        , gradientId(gradientId)
    {
        data_min = *std::min_element(data.begin(), data.end());
        data_max = *std::max_element(data.begin(), data.end());
    }

    void bind(I_Shader& shader)
    {
        vb.bind();

        shader.bind();
        shader.enableAttribute("a_data", 1, GL_FLOAT, GL_FALSE, sizeof(float), 0);
        shader.setUniform1f("u_data_min", data_min);
        shader.setUniform1f("u_data_max", data_max);

        auto& colorMap = colorMapRepository.lookup(gradientId);
        colorMap.bind(0);
        shader.setUniform1i("u_texture0", 0);
    }

    VertexBuffer vb;
    I_Repository<I_ColorMap>& colorMapRepository;
    IntegerId gradientId;

    float data_min = 0.0;
    float data_max = 0.0;

};

ContinuousMapping::ContinuousMapping(
    const std::vector<float>& data,
    I_Repository<I_ColorMap>& colorMapRepository,
    const IntegerId& gradientId)
    : p_(std::make_unique<Impl>(data, colorMapRepository, gradientId))
{
}
ContinuousMapping::~ContinuousMapping()
{
}

MappingType ContinuousMapping::type() const
{
    return MappingType::Continuous;
}

void ContinuousMapping::bind(I_Shader& shader)
{
    p_->bind(shader);
}

void ContinuousMapping::setGradient(const IntegerId& gradient)
{
    p_->gradientId = gradient;
}
