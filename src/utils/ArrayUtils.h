#pragma once

#include <glm/glm.hpp>

namespace ArrayUtils
{

unsigned int calculateIndex(unsigned int x, unsigned int y, unsigned int z, const glm::vec3& dims);

};
