#pragma once
#include "IntegerId.h"
#include <glm/glm.hpp>
#include <vector>

class I_ChunkManager
{
public:
    virtual ~I_ChunkManager() = default;

    virtual const std::vector<float>& vertices() const = 0;
};
