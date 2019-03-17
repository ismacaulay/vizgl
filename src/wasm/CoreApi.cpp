
#include <emscripten/emscripten.h>

#include "CoreInstance.h"

extern "C" {

EMSCRIPTEN_KEEPALIVE
void reset() {
    CoreInstance::reset();
}

}
