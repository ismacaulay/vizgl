#include "VoxelGeometry.h"

#include <functional>

#include "I_VoxelEngine.h"
#include "BoundingBox.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "I_Shader.h"
#include "MeshUtils.h"

#include <GLES2/gl2.h>
#include "GLError.h"

class VoxelVertexBuffer
{
public:
    VoxelVertexBuffer(const std::vector<float>& verts)
        : vb(std::make_unique<VertexBuffer>(verts.data(), verts.size() * sizeof(float)))
        , count(verts.size() / ValuesPerVertex)
    {
    }

    std::unique_ptr<VertexBuffer> vb;
    unsigned int count;

    static const unsigned int ValuesPerVertex = 6;
    static const unsigned int Stride = sizeof(float) * ValuesPerVertex;
    static const unsigned int PositionOffset = 0;
    static const unsigned int BarycentricOffset = sizeof(float) * 3;
};

class VoxelGeometry::Impl
{
public:
    Impl(const IntegerId& id, I_VoxelEngine& engine)
        : id(id)
        , engine(engine)
    {
        // engine.onChanged(meshId, [this](){ update(); });
        update();
    }

    void update()
    {
        const auto& mesh = engine.mesh(id);
        const auto& vertices = mesh.vertices();

        std::vector<float> verts;
        verts.reserve(vertices.size() * VoxelVertexBuffer::ValuesPerVertex);
        unsigned int vertexStride = 6;
        for (unsigned int i = 0; i < vertices.size() / vertexStride; i++) {
            {
                const auto& vert = vertices[(i * vertexStride) + 0];
                verts.push_back(vert.x); verts.push_back(vert.y); verts.push_back(vert.z);
                verts.push_back(1.0); verts.push_back(0.0); verts.push_back(0.0);
            }
            {
                const auto& vert = vertices[(i * vertexStride) + 1];
                verts.push_back(vert.x); verts.push_back(vert.y); verts.push_back(vert.z);
                verts.push_back(1.0); verts.push_back(1.0); verts.push_back(0.0);
            }
            {
                const auto& vert = vertices[(i * vertexStride) + 2];
                verts.push_back(vert.x); verts.push_back(vert.y); verts.push_back(vert.z);
                verts.push_back(1.0); verts.push_back(0.0); verts.push_back(1.0);
            }

            {
                const auto& vert = vertices[(i * vertexStride) + 3];
                verts.push_back(vert.x); verts.push_back(vert.y); verts.push_back(vert.z);
                verts.push_back(1.0); verts.push_back(1.0); verts.push_back(0.0);
            }
            {
                const auto& vert = vertices[(i * vertexStride) + 4];
                verts.push_back(vert.x); verts.push_back(vert.y); verts.push_back(vert.z);
                verts.push_back(1.0); verts.push_back(0.0); verts.push_back(0.0);
            }
            {
                const auto& vert = vertices[(i * vertexStride) + 5];
                verts.push_back(vert.x); verts.push_back(vert.y); verts.push_back(vert.z);
                verts.push_back(1.0); verts.push_back(0.0); verts.push_back(1.0);
            }

            if (verts.size() >= 2000000) {
                buffers.emplace_back(verts);
                verts.clear();
            }
        }

        if (verts.size() > 0) {
            buffers.emplace_back(verts);
        }

        boundingBox = MeshUtils::computeBoundingBox(vertices);
    }

    void render(I_Shader& shader)
    {
        shader.enableAttribute("a_position");
        shader.enableAttribute("a_barycentric");
        // shader.enableAttribute("a_data");
        for (auto& buffer : buffers) {
            buffer.vb->bind();
            shader.vertexAttributePointer(
                "a_position", 3, GL_FLOAT, GL_FALSE, VoxelVertexBuffer::Stride, VoxelVertexBuffer::PositionOffset);
            shader.vertexAttributePointer(
                "a_barycentric", 3, GL_FLOAT, GL_FALSE, VoxelVertexBuffer::Stride, VoxelVertexBuffer::BarycentricOffset);
            // shader.vertexAttributePointer("a_data", 3, GL_FLOAT, GL_FALSE, stride, 24);
            GL_CALL(glDrawArrays(GL_TRIANGLES, 0, buffer.count));
        }
    }

    IntegerId id;
    I_VoxelEngine& engine;

    std::vector<VoxelVertexBuffer> buffers;

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

void VoxelGeometry::render(I_Shader& shader)
{
    p_->render(shader);
}

const IntegerId& VoxelGeometry::id() const
{
    return p_->id;
}
