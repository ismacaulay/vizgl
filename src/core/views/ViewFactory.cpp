#include "ViewFactory.h"

#include "MeshView.h"

I_View* ViewFactory::createMesh(const std::vector<float>& vertices)
{
    return new MeshView(vertices);
}
