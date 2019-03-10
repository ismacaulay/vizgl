#pragma once
#include <vector>
#include "BoundingBox.h"

namespace MeshUtils
{

BoundingBox computeBoundingBox(const std::vector<float>& vertices);

}
