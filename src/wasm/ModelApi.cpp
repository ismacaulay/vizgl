
#include <emscripten/emscripten.h>

#include "CoreInstance.h"

extern "C" {

EMSCRIPTEN_KEEPALIVE
unsigned int createModel(unsigned int geometryId, unsigned int mappingId) {
    auto id = CoreInstance::getInstance().modelApi().createModel(
        IntegerId(geometryId),
        IntegerId(mappingId)
    );
    return id.value();
}

}
