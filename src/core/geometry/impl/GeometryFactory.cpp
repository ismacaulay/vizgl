#include "GeometryFactory.h"

#include "MeshGeometry.h"

std::shared_ptr<I_Geometry> GeometryFactory::createMesh(const std::vector<float>& vertices)
{
    return std::make_shared<MeshGeometry>(vertices);
}
