
#include <emscripten/emscripten.h>

#include "CoreInstance.h"
#include <stdio.h>

extern "C" {

EMSCRIPTEN_KEEPALIVE
unsigned int createMesh(float* vertices, int numVertices) {
    std::vector<float> verts(vertices, vertices + numVertices);

    auto geometryId = CoreInstance::getInstance().geometryApi().createMesh(verts);
    return geometryId.value();
}

EMSCRIPTEN_KEEPALIVE
unsigned int createMesh2(float* vertices, int numVertices, uint32_t* triangles, int numTriangles) {
    std::vector<float> verts(vertices, vertices + numVertices);
    std::vector<uint32_t> tris(triangles, triangles + numTriangles);

    auto geometryId = CoreInstance::getInstance().geometryApi().createMesh(verts, tris);
    return geometryId.value();
}

EMSCRIPTEN_KEEPALIVE
unsigned int createVoxelMesh(uint32_t* dims) {
    glm::vec3 d(dims[0], dims[1], dims[2]);

    auto geometryId = CoreInstance::getInstance().geometryApi().createVoxelMesh(d);
    return geometryId.value();
}

}
