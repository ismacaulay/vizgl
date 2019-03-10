#include "MeshUtils.h"

#include <glm/glm.hpp>

namespace MeshUtils {

BoundingBox computeBoundingBox(const std::vector<float>& vertices)
{
    float min_x = std::numeric_limits<float>::max();
    float max_x = std::numeric_limits<float>::min();

    float min_y = std::numeric_limits<float>::max();
    float max_y = std::numeric_limits<float>::min();

    float min_z = std::numeric_limits<float>::max();
    float max_z = std::numeric_limits<float>::min();

    for (int i = 0; i < vertices.size() / 3; i++) {
        float x = vertices[(i * 3) + 0];
        float y = vertices[(i * 3) + 1];
        float z = vertices[(i * 3) + 2];

        min_x = std::min(x, min_x);
        max_x = std::max(x, max_x);

        min_y = std::min(y, min_y);
        max_y = std::max(y, max_y);

        min_z = std::min(z, min_z);
        max_z = std::max(z, max_z);
    }

    return { glm::vec2(min_x, max_x), glm::vec2(min_y, max_y), glm::vec2(min_z, max_z) };
}

BoundingBox addVerticesToBoundingBox(const BoundingBox& initial, const std::vector<float>& vertices)
{
    auto bb = computeBoundingBox(vertices);

    float min_x = std::min(initial.x.x, bb.x.x);
    float max_x = std::max(initial.x.y, bb.x.y);

    float min_y = std::min(initial.y.x, bb.y.x);
    float max_y = std::max(initial.y.y, bb.y.y);

    float min_z = std::min(initial.z.x, bb.z.x);
    float max_z = std::max(initial.z.y, bb.z.y);

    return { glm::vec2(min_x, max_x), glm::vec2(min_y, max_y), glm::vec2(min_z, max_z) };
}

}
