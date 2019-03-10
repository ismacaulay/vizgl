#pragma once
#include <vector>
#include "BoundingBox.h"

namespace MeshUtils
{

BoundingBox computeBoundingBox(const std::vector<float>& vertices);
BoundingBox addVerticesToBoundingBox(const BoundingBox& initial, const std::vector<float>& vertices);

}
