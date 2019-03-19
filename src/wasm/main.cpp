#include <emscripten/emscripten.h>
#include <emscripten/html5.h>

#include "CoreInstance.h"

#include <stdio.h>

void main_loop()
{
    CoreInstance::getInstance().render();
}

int mouse_down_callback(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData)
{
    CoreInstance::getInstance().cameraApi().start(mouseEvent->button, mouseEvent->clientX, mouseEvent->clientY);
    return true;
}

int mouse_up_callback(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData)
{
    CoreInstance::getInstance().cameraApi().finish();
    return true;
}

int mouse_move_callback(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData)
{
    CoreInstance::getInstance().cameraApi().update(mouseEvent->clientX, mouseEvent->clientY);
    return true;
}

int mouse_wheel_callback(int eventType, const EmscriptenWheelEvent *wheelEvent, void *userData)
{
    CoreInstance::getInstance().cameraApi().zoom(wheelEvent->deltaY);
    return true;
}

int resize_callback(int type, const EmscriptenUiEvent *event, void *data)
{
    if (type == EMSCRIPTEN_EVENT_RESIZE) {
        double width, height;
        // use this if not using full screen
        emscripten_get_element_css_size("#canvas", &width, &height);
        emscripten_set_canvas_element_size("#canvas", int(width), int(height));

        // emscripten_get_canvas_element_size("#canvas", &width, &height);
        CoreInstance::getInstance().setSize(int(width), int(height));
    }

    return 1;
}

EMSCRIPTEN_KEEPALIVE
int main() {
    EmscriptenWebGLContextAttributes attrs;
    emscripten_webgl_init_context_attributes(&attrs);

    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context = emscripten_webgl_create_context("#canvas", &attrs);
    if (context == 0) {
        EM_ASM("document.body.innerText = 'Your browser does not support WebGL.';");
        return -1;
    }

    EMSCRIPTEN_RESULT result = emscripten_webgl_make_context_current(context);
    if (EMSCRIPTEN_RESULT_SUCCESS != result) {
        EM_ASM("document.body.innerText = 'Your browser does not support WebGL.';");
        return -1;
    }

    // EmscriptenFullscreenStrategy strategy;
    // strategy.scaleMode = EMSCRIPTEN_FULLSCREEN_SCALE_DEFAULT;
    // strategy.canvasResolutionScaleMode = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_STDDEF;
    // strategy.filteringMode = EMSCRIPTEN_FULLSCREEN_FILTERING_DEFAULT;
    // result = emscripten_enter_soft_fullscreen("canvas", &strategy);
    // if (EMSCRIPTEN_RESULT_SUCCESS != result) {
    //     EM_ASM("document.body.innerText = 'Error going to fullscreen';");
    //     return -1;
    // }


    emscripten_set_mousedown_callback("#canvas", nullptr, true, &mouse_down_callback);
    emscripten_set_mouseup_callback("#canvas", nullptr, true, &mouse_up_callback);
    emscripten_set_mousemove_callback("#canvas", nullptr, true, &mouse_move_callback);
    emscripten_set_wheel_callback("#canvas", nullptr, true, &mouse_wheel_callback);
    emscripten_set_resize_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, nullptr, true, &resize_callback);

    double width, height;
    // if not using full screen, need to set the canvas ourselves
    emscripten_get_element_css_size("#canvas", &width, &height);
    emscripten_set_canvas_element_size("#canvas", int(width), int(height));

    // emscripten_get_canvas_element_size("#canvas", &width, &height);
    CoreInstance::getInstance().setSize(width, height);

    emscripten_set_main_loop(main_loop, 0, true);

    emscripten_webgl_destroy_context(context);
    return 0;
}
