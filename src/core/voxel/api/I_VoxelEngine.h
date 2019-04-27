#pragma once

#include <functional>
#include <glm/glm.hpp>
#include <vector>

#include <bm-engine/mesh.h>

#include "IntegerId.h"

class I_VoxelEngine
{
public:
    virtual ~I_VoxelEngine() = default;

    virtual IntegerId generate(const glm::uvec3& dims) = 0;

    virtual void onChanged(const IntegerId& mesh, const std::function<void()>& cb) = 0;
    virtual void setData(const IntegerId& mesh, const std::vector<float>& data) = 0;

    virtual const bme::Mesh& mesh(const IntegerId& id) const = 0;
};
