#pragma once

class I_Shader;
class I_VertexBuffer;
struct BoundingBox;

enum class GeometryType
{
    Mesh,
    Voxel,
};

class I_Geometry
{
public:
    virtual ~I_Geometry() = default;

    virtual GeometryType type() const = 0;
    virtual const BoundingBox& boundingBox() const = 0;
    virtual unsigned int vertexCount() const = 0;

    virtual void render(I_Shader& shader) = 0;
};
