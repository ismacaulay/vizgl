
#include <emscripten/emscripten.h>

#include "CoreInstance.h"

extern "C" {

EMSCRIPTEN_KEEPALIVE
unsigned int createColorMap(int8_t* colors, int numColors) {
    std::vector<unsigned char> rgbColors(colors, colors + numColors);
    auto id = CoreInstance::getInstance().colorMapApi().createColorMap(rgbColors);
    return id.value();
}

}
