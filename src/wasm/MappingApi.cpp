
#include <emscripten/emscripten.h>

#include "CoreInstance.h"

extern "C" {

EMSCRIPTEN_KEEPALIVE
unsigned int createStaticMapping(uint8_t* color) {
    glm::vec3 rgbColor(color[0], color[1], color[2]);

    auto id = CoreInstance::getInstance().mappingApi().createStaticMapping(rgbColor);
    return id.value();
}

EMSCRIPTEN_KEEPALIVE
unsigned int createContinuousMapping(float* data, unsigned int numData, unsigned int gradientId) {
    std::vector<float> d(data, data + numData);

    auto id = CoreInstance::getInstance().mappingApi().createContinuousMapping(
        d,
        IntegerId(gradientId)
    );
    return id.value();
}

}
