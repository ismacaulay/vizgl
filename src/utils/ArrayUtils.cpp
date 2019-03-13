#include "ArrayUtils.h"

namespace ArrayUtils
{

unsigned int calculateIndex(unsigned int x, unsigned int y, unsigned int z, const glm::vec3& dims)
{
    // row major (c order): (x * dims.y * dims.z) + (y * dims.z) + z;
    // col major (f order): (z * dims.x * dims.y) + (y * dims.x) + x;
    return (x * dims.y * dims.z) + (y * dims.z) + z;
}

}
