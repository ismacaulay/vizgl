#include "ViewFactory.h"

#include "MeshView.h"

I_View* ViewFactory::createMesh(
    const std::vector<float>& vertices,
    const glm::vec4& color)
{
    return new MeshView(vertices, color);
}
