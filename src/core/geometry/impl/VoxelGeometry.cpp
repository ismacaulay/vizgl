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

    static const unsigned int ValuesPerVertex = 9;
};

class VoxelGeometry::Impl
{
public:
    Impl(const IntegerId& id, I_VoxelEngine& engine)
        : voxelMeshId(id)
        , engine(engine)
    {
        engine.onChanged(voxelMeshId, [this](){ update(); });

        update();
    }

    void update()
    {
        buffers.clear();

        const auto& dims = engine.dims(voxelMeshId);
        std::vector<float> verts;
        for(int k = 0; k < dims.z; k++) {
            for(int j = 0; j < dims.y; j++) {
                for(int i = 0; i < dims.x; i++) {
                    std::vector<float> nextVerts = engine.vertices(voxelMeshId, i, j, k);
                    verts.insert(verts.end(), nextVerts.begin(), nextVerts.end());
                    if (verts.size() >= 2000000) {
                        buffers.emplace_back(verts);
                        boundingBox = MeshUtils::addVerticesToBoundingBox(boundingBox, verts);
                        verts.clear();
                    }
                }
            }
        }

        if (verts.size() > 0) {
            buffers.emplace_back(verts);
            boundingBox = MeshUtils::addVerticesToBoundingBox(boundingBox, verts);
            verts.clear();
        }
    }

    void render(I_Shader& shader)
    {
        shader.enableAttribute("a_position");
        shader.enableAttribute("a_barycentric");
        shader.enableAttribute("a_data");
        unsigned int stride = VoxelVertexBuffer::ValuesPerVertex * sizeof(float);
        for (auto& buffer : buffers) {
            buffer.vb->bind();
            shader.vertexAttributePointer("a_position", 3, GL_FLOAT, GL_FALSE, stride, 0);
            shader.vertexAttributePointer("a_barycentric", 3, GL_FLOAT, GL_FALSE, stride, 12);
            shader.vertexAttributePointer("a_data", 3, GL_FLOAT, GL_FALSE, stride, 24);
            GL_CALL(glDrawArrays(GL_TRIANGLES, 0, buffer.count));
        }
    }

    IntegerId voxelMeshId;
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

const IntegerId& VoxelGeometry::voxelMeshId() const
{
    return p_->voxelMeshId;
}
