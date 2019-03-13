#include "MeshGeometry.h"

#include "BoundingBox.h"
#include "I_Shader.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "MeshUtils.h"

#include <GLES2/gl2.h>
#include "GLError.h"

class MeshGeometry::Impl
{
public:
    Impl(const std::vector<float>& vertices)
        : vb(vertices.data(), vertices.size() * sizeof(float))
        , layout()
        , boundingBox(MeshUtils::computeBoundingBox(vertices))
    {
        layout.push<float>(3);
        vertexCount = vertices.size() / 3;
    }

    void render(I_Shader& shader)
    {
        vb.bind();
        shader.enableAttribute("a_position");
        shader.vertexAttributePointer("a_position", 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
        GL_CALL(glDrawArrays(GL_TRIANGLES, 0, vertexCount));
    }

    VertexBuffer vb;
    VertexBufferLayout layout;
    BoundingBox boundingBox;
    unsigned int vertexCount;
};


MeshGeometry::MeshGeometry(const std::vector<float>& vertices)
    : p_(std::make_unique<Impl>(vertices))
{
}
MeshGeometry::~MeshGeometry()
{
}

GeometryType MeshGeometry::type() const
{
    return GeometryType::Mesh;
}

const BoundingBox& MeshGeometry::boundingBox() const
{
    return p_->boundingBox;
}

unsigned int MeshGeometry::vertexCount() const
{
    return p_->vertexCount;
}

void MeshGeometry::render(I_Shader& shader)
{
    p_->render(shader);
}
