#include "MathUtils.h"

namespace MathUtils
{

float sum(const std::vector<float>& v)
{
    return sum_to_index(v, static_cast<unsigned int>(v.size()));
}

float sum_to_index(const std::vector<float>& v, unsigned int index)
{
    float total = 0.0;
    for(int i = 0; i < index; i++) {
        total += v[i];
    }
    return total;
}

}
