
#include <emscripten/emscripten.h>
#include <stdio.h>

#include "CoreInstance.h"

extern "C" {

EMSCRIPTEN_KEEPALIVE
void createMesh(float* vertices, int numVertices) {
    printf("[createMesh] %d\n", numVertices);

    std::vector<float> v(vertices, vertices + numVertices);
    CoreInstance::getInstance().viewApi().createMesh(v);
}

EMSCRIPTEN_KEEPALIVE
void createMesh2(float* vertices, int numVertices, uint32_t* indices, int numIndices) {
    printf("[createMesh2] %d %d\n", numVertices, numIndices);

    std::vector<float> v(vertices, vertices + numVertices);
    std::vector<uint32_t> i(indices, indices + numIndices);

    CoreInstance::getInstance().viewApi().createMesh(v, i);
}

}
