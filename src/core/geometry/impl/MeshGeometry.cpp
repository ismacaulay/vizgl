#include "MeshGeometry.h"

#include "BoundingBox.h"
#include "I_Shader.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

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

class MeshGeometry::Impl
{
public:
    Impl(const std::vector<float>& vertices)
        : vb(vertices.data(), vertices.size() * sizeof(float))
        , layout()
        , boundingBox(computeBoundingBox(vertices))
    {
        layout.push<float>(3);
        vertexCount = vertices.size() / 3;
    }

    void bind(I_Shader& shader)
    {
        vb.bind();
        shader.bind();

        shader.enableAttribute("a_position", 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
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

void MeshGeometry::bind(I_Shader& shader)
{
    p_->bind(shader);
}
