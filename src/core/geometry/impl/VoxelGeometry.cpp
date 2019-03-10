#include "VoxelGeometry.h"

#include "I_VoxelEngine.h"
#include "BoundingBox.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "I_Shader.h"
#include "MeshUtils.h"

class VoxelGeometry::Impl
{
public:
    Impl(const IntegerId& id, I_VoxelEngine& engine)
    {
        const auto& vertices = engine.vertices(id);
        printf("[VoxelGeometry] verts: %lu\n", vertices.size());

        vb.setData(vertices.data(), vertices.size() * sizeof(float));
        boundingBox = MeshUtils::computeBoundingBox(vertices);
        printf("[VoxelGeometry] bb: x %f %f, y %f %f, z %f %f \n", boundingBox.x.x, boundingBox.x.y, boundingBox.y.x, boundingBox.y.y, boundingBox.z.x, boundingBox.z.y);

        layout.push<float>(3);
        vertexCount = vertices.size() / 6;
    }

    void bind(I_Shader& shader)
    {
        vb.bind();
        shader.enableAttribute("a_position", 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
        shader.enableAttribute("a_color", 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 12);
    }

    VertexBuffer vb;
    VertexBufferLayout layout;

    BoundingBox boundingBox;
    unsigned int vertexCount;
};

VoxelGeometry::VoxelGeometry(const IntegerId& id, I_VoxelEngine& engine)
    : p_(std::make_unique<Impl>(id, engine))
{
}
VoxelGeometry::~VoxelGeometry()
{
}

GeometryType VoxelGeometry::type() const
{
    return GeometryType::Voxel;
}

const BoundingBox& VoxelGeometry::boundingBox() const
{
    return p_->boundingBox;
}

unsigned int VoxelGeometry::vertexCount() const
{
    return p_->vertexCount;
}

void VoxelGeometry::bind(I_Shader& shader)
{
    p_->bind(shader);
}
