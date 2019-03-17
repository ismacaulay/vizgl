
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>

#include "CoreInstance.h"

extern "C" {

EMSCRIPTEN_KEEPALIVE
void reset() {
    CoreInstance::reset();

    double width, height;
    emscripten_get_element_css_size("#canvas", &width, &height);
    emscripten_set_canvas_element_size("#canvas", int(width), int(height));

    CoreInstance::getInstance().setSize(int(width), int(height));
}

}
