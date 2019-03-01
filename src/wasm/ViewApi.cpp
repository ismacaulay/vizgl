
#include <emscripten/emscripten.h>

#include "CoreInstance.h"

extern "C" {

EMSCRIPTEN_KEEPALIVE
void createMesh(float* vertices, int numVertices) {
    std::vector<float> verts(vertices, vertices + numVertices);
    glm::vec3 color(0.1, 0.2, 0.3);

    auto geometryId = CoreInstance::getInstance().geometryApi().createMesh(verts);
    auto mappingId = CoreInstance::getInstance().mappingApi().createStaticMapping(color);

    CoreInstance::getInstance().modelApi().createModel(geometryId, mappingId);
}

EMSCRIPTEN_KEEPALIVE
void createMesh2(float* vertices, int numVertices, uint32_t* triangles, int numTriangles) {

    std::vector<float> verts(vertices, vertices + numVertices);
    std::vector<uint32_t> tris(triangles, triangles + numTriangles);
    glm::vec3 color(0.1, 0.2, 0.3);

    auto geometryId = CoreInstance::getInstance().geometryApi().createMesh(verts, tris);
    auto mappingId = CoreInstance::getInstance().mappingApi().createStaticMapping(color);

    CoreInstance::getInstance().modelApi().createModel(geometryId, mappingId);
}

}
