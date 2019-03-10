#pragma once
#include <functional>
#include <glm/glm.hpp>
#include <vector>

#include "IntegerId.h"

class I_ChunkManager
{
public:
    virtual ~I_ChunkManager() = default;

    virtual void onChanged(const std::function<void()>& cb) = 0;
    virtual void setData(const std::vector<float>& data) = 0;

    virtual const glm::vec3& dims() const = 0;
    virtual std::vector<float> vertices(unsigned int x, unsigned int y, unsigned int z) const = 0;
};
