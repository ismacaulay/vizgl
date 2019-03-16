
#include <emscripten/emscripten.h>

#include "CoreInstance.h"

extern "C" {

EMSCRIPTEN_KEEPALIVE
void setPlotRotation(float* rotation) {
    glm::vec3 rot(rotation[0], rotation[1], rotation[2]);
    CoreInstance::getInstance().plotApi().setRotation(rot);
}

}
