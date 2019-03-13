#pragma once
#include "I_Mapping.h"

#include <glm/glm.hpp>

class StaticMapping : public I_Mapping
{
public:
    explicit StaticMapping(const glm::vec3& rgb, bool wireframe);
    ~StaticMapping() = default;

    MappingType type() const;
    void bind(I_Shader& shader);

    void setGradient(const IntegerId& gradient);

private:
    glm::vec3 normalizedColor_;
    bool wireframe_;
};
