#include <emscripten/emscripten.h>
#include <emscripten/html5.h>

#include "CoreInstance.h"

// std::vector<float> CUBE_VERTICES = {
//     // positions          // color       // tex coords
//     -0.5f, -0.5f, -0.5f,  1.0, 0.0, 0.0, //0.0f, 0.0f,
//      0.5f, -0.5f, -0.5f,  1.0, 0.0, 0.0, //1.0f, 0.0f,
//      0.5f,  0.5f, -0.5f,  1.0, 0.0, 0.0, //1.0f, 1.0f,
//      0.5f,  0.5f, -0.5f,  1.0, 0.0, 0.0, //1.0f, 1.0f,
//     -0.5f,  0.5f, -0.5f,  1.0, 0.0, 0.0, //0.0f, 1.0f,
//     -0.5f, -0.5f, -0.5f,  1.0, 0.0, 0.0, //0.0f, 0.0f,

//     -0.5f, -0.5f,  0.5f,  0.0, 1.0, 0.0, //0.0f, 0.0f,
//      0.5f, -0.5f,  0.5f,  0.0, 1.0, 0.0, //1.0f, 0.0f,
//      0.5f,  0.5f,  0.5f,  0.0, 1.0, 0.0, //1.0f, 1.0f,
//      0.5f,  0.5f,  0.5f,  0.0, 1.0, 0.0, //1.0f, 1.0f,
//     -0.5f,  0.5f,  0.5f,  0.0, 1.0, 0.0, //0.0f, 1.0f,
//     -0.5f, -0.5f,  0.5f,  0.0, 1.0, 0.0, //0.0f, 0.0f,

//     -0.5f,  0.5f,  0.5f,  0.0, 0.0, 1.0, //1.0f, 0.0f,
//     -0.5f,  0.5f, -0.5f,  0.0, 0.0, 1.0, //1.0f, 1.0f,
//     -0.5f, -0.5f, -0.5f,  0.0, 0.0, 1.0, //0.0f, 1.0f,
//     -0.5f, -0.5f, -0.5f,  0.0, 0.0, 1.0, //0.0f, 1.0f,
//     -0.5f, -0.5f,  0.5f,  0.0, 0.0, 1.0, //0.0f, 0.0f,
//     -0.5f,  0.5f,  0.5f,  0.0, 0.0, 1.0, //1.0f, 0.0f,

//     0.5f,  0.5f,  0.5f,  1.0, 1.0, 0.0, //1.0f, 0.0f,
//     0.5f,  0.5f, -0.5f,  1.0, 1.0, 0.0, //1.0f, 1.0f,
//     0.5f, -0.5f, -0.5f,  1.0, 1.0, 0.0, //0.0f, 1.0f,
//     0.5f, -0.5f, -0.5f,  1.0, 1.0, 0.0, //0.0f, 1.0f,
//     0.5f, -0.5f,  0.5f,  1.0, 1.0, 0.0, //0.0f, 0.0f,
//     0.5f,  0.5f,  0.5f,  1.0, 1.0, 0.0, //1.0f, 0.0f,

//     -0.5f, -0.5f, -0.5f,  0.0, 1.0, 1.0, //0.0f, 1.0f,
//      0.5f, -0.5f, -0.5f,  0.0, 1.0, 1.0, //1.0f, 1.0f,
//      0.5f, -0.5f,  0.5f,  0.0, 1.0, 1.0, //1.0f, 0.0f,
//      0.5f, -0.5f,  0.5f,  0.0, 1.0, 1.0, //1.0f, 0.0f,
//     -0.5f, -0.5f,  0.5f,  0.0, 1.0, 1.0, //0.0f, 0.0f,
//     -0.5f, -0.5f, -0.5f,  0.0, 1.0, 1.0, //0.0f, 1.0f,

//     -0.5f,  0.5f, -0.5f,  1.0, 0.0, 1.0, //0.0f, 1.0f,
//      0.5f,  0.5f, -0.5f,  1.0, 0.0, 1.0, //1.0f, 1.0f,
//      0.5f,  0.5f,  0.5f,  1.0, 0.0, 1.0, //1.0f, 0.0f,
//      0.5f,  0.5f,  0.5f,  1.0, 0.0, 1.0, //1.0f, 0.0f,
//     -0.5f,  0.5f,  0.5f,  1.0, 0.0, 1.0, //0.0f, 0.0f,
//     -0.5f,  0.5f, -0.5f,  1.0, 0.0, 1.0, //0.0f, 1.0f
// };

void main_loop() {
    CoreInstance::getInstance().render();
}

int mouse_down_callback(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData)
{
    CoreInstance::getInstance().cameraApi().start(mouseEvent->button, mouseEvent->canvasX, mouseEvent->canvasY);
    return 0;
}

int mouse_up_callback(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData)
{
    CoreInstance::getInstance().cameraApi().finish();
    return 0;
}

int mouse_move_callback(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData)
{
    CoreInstance::getInstance().cameraApi().update(mouseEvent->canvasX, mouseEvent->canvasY);
    return 0;
}

int mouse_wheel_callback(int eventType, const EmscriptenWheelEvent *wheelEvent, void *userData)
{
    CoreInstance::getInstance().cameraApi().zoom(wheelEvent->deltaY);
    return 0;
}

int resize_callback(int type, const EmscriptenUiEvent *event, void *data)
{
    if (type == EMSCRIPTEN_EVENT_RESIZE)
    {
        int width, height;
        emscripten_get_canvas_element_size("canvas", &width, &height);
        CoreInstance::getInstance().setSize(width, height);
    }

    return 0;
}

EMSCRIPTEN_KEEPALIVE int main() {
    EmscriptenWebGLContextAttributes attrs;
    emscripten_webgl_init_context_attributes(&attrs);

    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context = emscripten_webgl_create_context(nullptr, &attrs);
    if (context == 0)
    {
        EM_ASM("document.body.innerText = 'Your browser does not support WebGL.';");
        return -1;
    }

    EMSCRIPTEN_RESULT result = emscripten_webgl_make_context_current(context);
    if (EMSCRIPTEN_RESULT_SUCCESS != result)
    {
        EM_ASM("document.body.innerText = 'Your browser does not support WebGL.';");
        return -1;
    }

    EmscriptenFullscreenStrategy strategy;
    strategy.scaleMode = EMSCRIPTEN_FULLSCREEN_SCALE_DEFAULT;
    strategy.canvasResolutionScaleMode = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_STDDEF;
    strategy.filteringMode = EMSCRIPTEN_FULLSCREEN_FILTERING_DEFAULT;
    result = emscripten_enter_soft_fullscreen("canvas", &strategy);
    if (EMSCRIPTEN_RESULT_SUCCESS != result)
    {
        EM_ASM("document.body.innerText = 'Error going to fullscreen';");
        return -1;
    }

    emscripten_set_mousedown_callback(nullptr, nullptr, true, &mouse_down_callback);
    emscripten_set_mouseup_callback(nullptr, nullptr, true, &mouse_up_callback);
    emscripten_set_mousemove_callback(nullptr, nullptr, true, &mouse_move_callback);
    emscripten_set_wheel_callback(nullptr, nullptr, true, &mouse_wheel_callback);

    emscripten_set_resize_callback(nullptr, nullptr, true, &resize_callback);

    int width, height;
    emscripten_get_canvas_element_size("canvas", &width, &height);
    CoreInstance::getInstance().setSize(width, height);

    // std::vector<float> vertices = {
    //     // positions       // colors         // tex coords
    //     -0.5f, -0.5f, 0.0, 1.0f, 0.0f, 0.0f, // 0.0f, 0.0f, // 0: x, y, s, t
    //      0.5f, -0.5f, 0.0, 0.0f, 1.0f, 0.0f, // 1.0f, 0.0f, // 1
    //      0.0f,  0.5f, 0.0, 0.0f, 0.0f, 1.0f, // 1.0f, 1.0f, // 2
    //     //-0.5f,  0.5f, 0.0, 1.0f, 1.0f, 0.0f, // 0.0f, 1.0f, // 3
    // };
    // CoreInstance::getInstance().viewApi().createMesh(CUBE_VERTICES);

    emscripten_set_main_loop(main_loop, 0, true);
    return 0;
}
