#pragma once
#include "I_Mapping.h"

#include <unordered_map>
#include <glm/glm.hpp>

class StaticMapping : public I_Mapping
{
public:
    explicit StaticMapping(const glm::vec3& rgb);
    ~StaticMapping() = default;

    MappingType type() const;
    void bind(I_Shader& shader);

private:
    glm::vec3 rgb_;
    std::unordered_map<int, int> uniformLocationCache_;
};
