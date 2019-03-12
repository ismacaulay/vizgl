#include "ArrayUtils.h"

namespace ArrayUtils
{

unsigned int calculateIndex(unsigned int x, unsigned int y, unsigned int z, const glm::vec3& dims)
{
    return (z * dims.x * dims.y) + (y * dims.x) + x;
}

}
