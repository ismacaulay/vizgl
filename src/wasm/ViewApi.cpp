#include <cstdint>

#include "CoreInstance.h"
#include <stdio.h>

extern "C" {

void createMesh(float* vertices, int numVertices) {
    printf("[createMesh] %d\n", numVertices);

    std::vector<float> v(vertices, vertices + numVertices);

    CoreInstance::getInstance().viewApi().createMesh(v);
}

void createMesh2(float* vertices, int numVertices, uint32_t* indices, int numIndices) {
    printf("[createMesh2] %d %d\n", numVertices, numIndices);

    std::vector<float> v(vertices, vertices + numVertices);
    std::vector<uint32_t> i(indices, indices + numIndices);

    CoreInstance::getInstance().viewApi().createMesh(v, i);
}

}
