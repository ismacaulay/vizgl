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
        , count(verts.size() / 3)
    {
    }

    std::unique_ptr<VertexBuffer> vb;
    unsigned int count;
};

class VoxelGeometry::Impl
{
public:
    Impl(const IntegerId& id, I_VoxelEngine& engine)
        : voxelMeshId(id)
        , engine(engine)
        // , vb(nullptr)
    {
        engine.onChanged(voxelMeshId, [this](){ update(); });

        update();
    }

    void update()
    {
        const auto& dims = engine.dims(voxelMeshId);
        std::vector<float> verts;
        for(int k = 0; k < dims.z; k++) {
            for(int j = 0; j < dims.y; j++) {
                for(int i = 0; i < dims.x; i++) {
                    std::vector<float> nextVerts = engine.vertices(voxelMeshId, i, j, k);
                    verts.insert(verts.end(), nextVerts.begin(), nextVerts.end());
                    // printf("[VoxelGeometry] verts: %lu\n", verts.size());

                    if (verts.size() >= 1000000) {
                        buffers.emplace_back(verts);
                        boundingBox = MeshUtils::addVerticesToBoundingBox(boundingBox, verts);
                        verts.clear();
                    }

                    // vertexCount += verts.size() / 3;
                }
            }
        }

        if (verts.size() > 0) {
            buffers.emplace_back(verts);
            boundingBox = MeshUtils::addVerticesToBoundingBox(boundingBox, verts);
            verts.clear();
        }

        // const auto& vertices = engine.vertices(voxelMeshId);
        // printf("[VoxelGeometry] verts: %lu\n", vertices.size());

        // vb = std::make_unique<VertexBuffer>(vertices.data(), vertices.size() * sizeof(float));

        // boundingBox = MeshUtils::computeBoundingBox(vertices);
        printf("[VoxelGeometry] bb: x %f %f, y %f %f, z %f %f \n", boundingBox.x.x, boundingBox.x.y, boundingBox.y.x, boundingBox.y.y, boundingBox.z.x, boundingBox.z.y);

        // vertexCount = vertices.size() / 3;
    }

    // void bind(I_Shader& shader)
    // {
    //     // vb->bind();
    // }

    void render(I_Shader& shader)
    {
        shader.enableAttribute("a_position");
        for (auto& buffer : buffers) {
            buffer.vb->bind();
            shader.vertexAttributePointer("a_position", 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
            GL_CALL(glDrawArrays(GL_TRIANGLES, 0, buffer.count));
        }
    }

    IntegerId voxelMeshId;
    I_VoxelEngine& engine;

    std::vector<VoxelVertexBuffer> buffers;
    // std::unique_ptr<VertexBuffer> vb;

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
