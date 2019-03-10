#pragma once

#include <functional>
#include <glm/glm.hpp>
#include <vector>

#include "IntegerId.h"

class I_VoxelEngine
{
public:
    virtual ~I_VoxelEngine() = default;

    virtual IntegerId generate(const glm::vec3& dims) = 0;

    virtual void onChanged(const IntegerId& mesh, const std::function<void()>& cb) = 0;
    virtual void setData(const IntegerId& mesh, const std::vector<float>& data) = 0;

    virtual const glm::vec3& dims(const IntegerId& mesh) const = 0;
    virtual std::vector<float> vertices(const IntegerId& mesh, unsigned int x, unsigned int y, unsigned int z) const = 0;
};
