
#include <emscripten/emscripten.h>

#include "CoreInstance.h"

extern "C" {

EMSCRIPTEN_KEEPALIVE
void createMesh(float* vertices, int numVertices) {
    std::vector<float> v(vertices, vertices + numVertices);
    CoreInstance::getInstance().viewApi().createMesh(v);
}

EMSCRIPTEN_KEEPALIVE
void createMesh2(float* vertices, int numVertices, uint32_t* indices, int numIndices) {
    std::vector<float> v(vertices, vertices + numVertices);
    std::vector<uint32_t> i(indices, indices + numIndices);

    CoreInstance::getInstance().viewApi().createMesh(v, i);
}

}
