/* Ported from: https://github.com/hef/imgui-in-browser/ */
#include "imgui_impl.h"

#include <imgui.h>
#include <stdio.h>
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

// #include "draw.h"
#define GL_CHECKED(command)\
    command;\
    for(int error = glGetError(); (error=glGetError()); error != GL_NO_ERROR)\
    {\
        emscripten_log(EM_LOG_CONSOLE|EM_LOG_C_STACK|EM_LOG_DEMANGLE, "glerror: %d", error);\
    }


#define DEBUGPRINT_KEYBOARD 1

const char* ImGuiImpl::vertexShader =
"uniform mat4 ProjMtx;                                  \n"
"attribute vec2 Position;                               \n"
"attribute vec2 UV;                                     \n"
"attribute vec4 Color;                                  \n"
"varying vec2 Frag_UV;                                  \n"
"varying vec4 Frag_Color;                               \n"
"void main()                                            \n"
"{                                                      \n"
"   Frag_UV = UV;                                       \n"
"   Frag_Color = Color;                                 \n"
"   gl_Position = ProjMtx * vec4(Position.xy, 0, 1);    \n"
"}                                                      \n";

const char* ImGuiImpl::fragmentShader =
"uniform sampler2D Texture;                                     \n"
"varying mediump vec2 Frag_UV;                                  \n"
"varying mediump vec4 Frag_Color;                               \n"
"void main()                                                    \n"
"{                                                              \n"
"   gl_FragColor = Frag_Color * texture2D(Texture, Frag_UV);    \n"
"}                                                              \n";

int ImGuiImpl::m_shaderHandle = -1;
int ImGuiImpl::m_texture = -1;
int ImGuiImpl::m_projectionMatrix = -1;
int ImGuiImpl::m_position = -1;
int ImGuiImpl::m_uv = -1;
int ImGuiImpl::m_color = -1;
unsigned int ImGuiImpl::m_vao = -1;
unsigned int ImGuiImpl::m_vbo = -1;
unsigned int ImGuiImpl::m_elements = -1;
unsigned int ImGuiImpl::m_fontTexture = -1;

void ImGuiImpl::init()
{
    ImGuiIO& io = ImGui::GetIO();

    io.KeyMap[ImGuiKey_Tab] = 9;
    io.KeyMap[ImGuiKey_LeftArrow] = 37;
    io.KeyMap[ImGuiKey_RightArrow] = 39;
    io.KeyMap[ImGuiKey_UpArrow] = 38;
    io.KeyMap[ImGuiKey_DownArrow] = 40;
    io.KeyMap[ImGuiKey_PageUp] = 33;
    io.KeyMap[ImGuiKey_PageDown] = 34;
    io.KeyMap[ImGuiKey_Home] = 36;
    io.KeyMap[ImGuiKey_End] = 35;
    io.KeyMap[ImGuiKey_Delete] = 46;
    io.KeyMap[ImGuiKey_Backspace] = 8;
    io.KeyMap[ImGuiKey_Enter] = 13;
    io.KeyMap[ImGuiKey_Escape] = 27;
    io.KeyMap[ImGuiKey_A] = 65;
    io.KeyMap[ImGuiKey_C] = 67;
    io.KeyMap[ImGuiKey_V] = 86;
    io.KeyMap[ImGuiKey_X] = 88;
    io.KeyMap[ImGuiKey_Y] = 89;
    io.KeyMap[ImGuiKey_Z] = 90;

    io.RenderDrawListsFn = RenderDrawLists;
    io.ClipboardUserData = nullptr;
    initGraphics();

    io.KeyRepeatDelay = 1.0f;
    io.KeyRepeatRate = 0.5f;

    //io.MouseDrawCursor = true;
    emscripten_set_mousemove_callback(nullptr, nullptr, false, &ImGuiImpl::mouseCallback);
    emscripten_set_mousedown_callback(nullptr, nullptr, false, &ImGuiImpl::mouseCallback);
    emscripten_set_mouseup_callback(nullptr, nullptr, false, &ImGuiImpl::mouseCallback);
    emscripten_set_wheel_callback("canvas", nullptr, false, &ImGuiImpl::wheelCallback);
    emscripten_set_wheel_callback("canvas", nullptr, false, &ImGuiImpl::wheelCallback);
    //emscripten_set_keypress_callback(nullptr, nullptr, false, &ImGuiImpl::keyboardCallback);
    emscripten_set_keydown_callback(nullptr, nullptr, false, &ImGuiImpl::keyboardCallback);
    emscripten_set_keyup_callback(nullptr, nullptr, false, &ImGuiImpl::keyboardCallback);

    //emscripten_request_pointerlock(nullptr, true);
    //printf("pixel ratio: %f\n", emscripten_get_device_pixel_ratio());
}

void ImGuiImpl::BeginFrame()
{
    ImGuiIO& io = ImGui::GetIO();
    int width = 0;
    int height = 0;
    // int display_w = 0;
    // int display_h = 0;
    //
    //
    //double ratio = emscripten_get_device_pixel_ratio();

    emscripten_get_canvas_element_size("canvas", &width, &height);
    io.DisplaySize = ImVec2((float)width, (float)height);
    io.DisplayFramebufferScale = ImVec2(1.f,1.f);
    /*io.DisplayFramebufferScale = ImVec2(
            width  > 0 ? ((float)display_w/width) : 0,
            height > 0 ? ((float)display_h/height): 0
    );*/

    static double last;
    double now = emscripten_get_now();
    io.DeltaTime = (float)(now - last)/1000.0;
    last = now;
    // ImGui::NewFrame();
}

void ImGuiImpl::RenderDrawLists(ImDrawData* drawData)
{
    ImGuiIO& io = ImGui::GetIO();
    int fb_width = io.DisplaySize.x * io.DisplayFramebufferScale.x;
    int fb_height = io.DisplaySize.y * io.DisplayFramebufferScale.y;

    //printf("size: %d, %d\n", fb_width, fb_height);

    if(fb_width == 0 || fb_height == 0)
        return;
    drawData->ScaleClipRects(io.DisplayFramebufferScale);

    GLint lastProgram; glGetIntegerv(GL_CURRENT_PROGRAM, &lastProgram);
    GLint lastTexture; glGetIntegerv(GL_TEXTURE_BINDING_2D, &lastTexture);
    GLint lastActiveTexture; glGetIntegerv(GL_ACTIVE_TEXTURE, &lastActiveTexture);
    GLint lastArrayBuffer; glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &lastArrayBuffer);
    GLint lastElementArrayBuffer; glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &lastElementArrayBuffer);
    GLint lastVertexArray; glGetIntegerv(GL_VERTEX_ARRAY_BINDING_OES, &lastVertexArray);
    //GLint lastBlendSrc; glGetIntegerv(GL_BLEND_SRC, &lastBlendSrc);
    //GLint lastBlendDst; glGetIntegerv(GL_BLEND_DST, &lastBlendDst);
    GLint lastBlendEquationRgb; glGetIntegerv(GL_BLEND_EQUATION_RGB, &lastBlendEquationRgb);
    GLint lastBlendEquationAlpha; glGetIntegerv(GL_BLEND_EQUATION_ALPHA, &lastBlendEquationAlpha);
    GLint lastViewport[4]; glGetIntegerv(GL_VIEWPORT, lastViewport);
    GLint lastScissorBox[4]; glGetIntegerv(GL_SCISSOR_BOX, lastScissorBox);
    GLboolean lastEnableBlend = glIsEnabled(GL_BLEND);
    GLboolean lastEnableCullFace = glIsEnabled(GL_CULL_FACE);
    GLboolean lastEnableDepthTest = glIsEnabled(GL_DEPTH_TEST);
    GLboolean lastEnableScissorTest = glIsEnabled(GL_SCISSOR_TEST);

    glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_SCISSOR_TEST);
    glActiveTexture(GL_TEXTURE0);

    glViewport(0, 0, (GLsizei)fb_width, (GLsizei)fb_height);

    const float orthProjection[4][4] =
    {
        { 2.0f/io.DisplaySize.x, 0.0f,                    0.0f, 0.0f },
        { 0.0f,                  2.0f/-io.DisplaySize.y,  0.0f, 0.0f },
        { 0.0f,                  0.0f,                   -1.0f, 0.0f },
        {-1.0f,                  1.0f,                    0.0f, 1.0f },
    };

    glUseProgram(m_shaderHandle);
    glUniform1i(m_texture, 0);
    glUniformMatrix4fv(m_projectionMatrix, 1, GL_FALSE, &orthProjection[0][0]);
    glBindVertexArrayOES(m_vao);

    for(int i=0; i < drawData->CmdListsCount; ++i)
    {
        const ImDrawList* cmdList = drawData->CmdLists[i];
        const ImDrawIdx* idxBufferOffset = nullptr;

        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)cmdList->VtxBuffer.Size * sizeof(ImDrawVert), (GLvoid*)cmdList->VtxBuffer.Data, GL_STREAM_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elements);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)cmdList->IdxBuffer.Size * sizeof(ImDrawIdx), (GLvoid*)cmdList->IdxBuffer.Data, GL_STREAM_DRAW);

        for(int j=0; j < cmdList->CmdBuffer.Size; ++j)
        {
            const ImDrawCmd* drawCommand = &cmdList->CmdBuffer[j];
            if(drawCommand->UserCallback)
            {
                drawCommand->UserCallback(cmdList, drawCommand);
            }
            else
            {
                glBindTexture(
                    GL_TEXTURE_2D,
                    (GLuint)(intptr_t)drawCommand->TextureId
                );
                glScissor(
                    (int)drawCommand->ClipRect.x,
                    (int)(fb_height - drawCommand->ClipRect.w),
                    (int)(drawCommand->ClipRect.z - drawCommand->ClipRect.x),
                    (int)(drawCommand->ClipRect.w - drawCommand->ClipRect.y)
                );
                glDrawElements(
                    GL_TRIANGLES,
                    (GLsizei)drawCommand->ElemCount,
                    sizeof(ImDrawIdx) == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT,
                    idxBufferOffset
                );
            }
            idxBufferOffset += drawCommand->ElemCount;
        }
    }
    glUseProgram(lastProgram);
    glActiveTexture(lastActiveTexture);
    glBindTexture(GL_TEXTURE_2D, lastTexture);
    glBindVertexArrayOES(lastVertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, lastArrayBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lastElementArrayBuffer);
    glBlendEquationSeparate(lastBlendEquationRgb, lastBlendEquationAlpha);
    //glBlendFunc(lastBlendSrc, lastBlendDst);
    if(lastEnableBlend) glEnable(GL_BLEND); else glDisable(GL_BLEND);
    if(lastEnableCullFace) glEnable(GL_CULL_FACE); else glDisable(GL_CULL_FACE);
    if(lastEnableDepthTest) glEnable(GL_DEPTH_TEST); else glDisable(GL_DEPTH_TEST);
    if(lastEnableScissorTest) glEnable(GL_SCISSOR_TEST); else glDisable(GL_SCISSOR_TEST);
    glViewport(lastViewport[0], lastViewport[1], (GLsizei)lastViewport[2], (GLsizei)lastViewport[3]);
    glScissor(lastScissorBox[0], lastScissorBox[1], (GLsizei)lastScissorBox[2], (GLsizei)lastScissorBox[3]);
}

void ImGuiImpl::initGraphics()
{
    GLint lastTexture;
    GLint lastArrayBuffer;
    GLint lastVertexArray;

    GL_CHECKED( glGetIntegerv(GL_TEXTURE_BINDING_2D, &lastTexture) );
    GL_CHECKED( glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &lastArrayBuffer) );
    GL_CHECKED( glGetIntegerv(GL_VERTEX_ARRAY_BINDING_OES, &lastVertexArray) );

    m_shaderHandle = glCreateProgram();
    GLint vertexHandle = glCreateShader(GL_VERTEX_SHADER);
    GLint fragmentHandle = glCreateShader(GL_FRAGMENT_SHADER);

    GL_CHECKED( glShaderSource(vertexHandle, 1, &vertexShader, 0) );
    GL_CHECKED( glShaderSource(fragmentHandle, 1, &fragmentShader, 0) );
    GL_CHECKED( glCompileShader(vertexHandle) );
    // Draw::shaderErrors(vertexHandle);
    GL_CHECKED( glCompileShader(fragmentHandle) );
    // Draw::shaderErrors(fragmentHandle);

    GL_CHECKED( glAttachShader(m_shaderHandle, vertexHandle) );
    GL_CHECKED( glAttachShader(m_shaderHandle, fragmentHandle) );

    GL_CHECKED( glLinkProgram(m_shaderHandle) );

    GL_CHECKED( m_texture = glGetUniformLocation(m_shaderHandle, "Texture") );
    GL_CHECKED( m_projectionMatrix = glGetUniformLocation(m_shaderHandle, "ProjMtx") );
    GL_CHECKED( m_position = glGetAttribLocation(m_shaderHandle, "Position") );
    GL_CHECKED( m_uv = glGetAttribLocation(m_shaderHandle, "UV") );
    GL_CHECKED( m_color = glGetAttribLocation(m_shaderHandle, "Color") );

    GL_CHECKED( glGenBuffers(1, &m_vbo) );
    GL_CHECKED( glGenBuffers(1, &m_elements) );

    GL_CHECKED( glGenVertexArraysOES(1, &m_vao) );
    GL_CHECKED( glBindVertexArrayOES(m_vao) );
    GL_CHECKED( glBindBuffer(GL_ARRAY_BUFFER, m_vbo) );
    GL_CHECKED( glEnableVertexAttribArray(m_position) );
    GL_CHECKED( glEnableVertexAttribArray(m_uv) );
    GL_CHECKED( glEnableVertexAttribArray(m_color) );
#define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))
    GL_CHECKED( glVertexAttribPointer(m_position, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid*)OFFSETOF(ImDrawVert, pos)) );
    GL_CHECKED( glVertexAttribPointer(m_uv, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid*)OFFSETOF(ImDrawVert, uv)) );
    GL_CHECKED( glVertexAttribPointer(m_color, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(ImDrawVert), (GLvoid*)OFFSETOF(ImDrawVert, col)) );
#undef OFFSETOF
    GL_CHECKED( glBindTexture(GL_TEXTURE_2D, lastTexture) );
    GL_CHECKED( glBindBuffer(GL_ARRAY_BUFFER, lastArrayBuffer) );
    GL_CHECKED( glBindVertexArrayOES(lastVertexArray) );
    initFont();
}

void ImGuiImpl::initFont()
{
    ImGuiIO& io = ImGui::GetIO();
    unsigned char* pixels = nullptr;
    int width = 0;
    int height = 0;
    io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

    GLint lastTexture;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &lastTexture);
    glGenTextures(1, &m_fontTexture);
    glBindTexture(GL_TEXTURE_2D, m_fontTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    io.Fonts->TexID = (void*)(intptr_t)m_fontTexture;
    glBindTexture(GL_TEXTURE_2D, lastTexture);

}

int ImGuiImpl::mouseCallback(int /*eventType*/, const EmscriptenMouseEvent* mouseEvent, void* /*userData*/)
{
    ImGuiIO& io = ImGui::GetIO();
    io.MousePos = ImVec2((float)mouseEvent->canvasX, (float)mouseEvent->canvasY);
    io.MouseDown[0] = mouseEvent->buttons & 1;
    io.MouseDown[1] = mouseEvent->buttons & 2;
    io.MouseDown[2] = mouseEvent->buttons & 4;
    return true;
}

int ImGuiImpl::wheelCallback(int /*eventType*/, const EmscriptenWheelEvent* wheelEvent, void* /*userData*/)
{
    ImGuiIO& io = ImGui::GetIO();
    if(wheelEvent->deltaY > 0)
        io.MouseWheel = -1.f/5.f;
    else if(wheelEvent->deltaY < 0)
        io.MouseWheel = 1.f/5.f;

    return true;
}

int ImGuiImpl::keyboardCallback(int eventType, const EmscriptenKeyboardEvent* keyEvent, void* /*userData*/)
{
    bool handled = true;
    ImGuiIO& io = ImGui::GetIO();
    //let copy paste fall through to browser
    if(
        (keyEvent->ctrlKey || keyEvent->metaKey) &&
        (
            0 == strcmp("KeyC", keyEvent->code) ||
            0 == strcmp("KeyV", keyEvent->code) ||
            0 == strcmp("KeyX", keyEvent->code)
        )
    )
    {
        handled = true;
    }

    //todo, detect a single unicode codepoint instead of a single character
    if(
        keyEvent->key[1] == '\0' &&
       eventType == EMSCRIPTEN_EVENT_KEYDOWN
    )
    {
        io.AddInputCharactersUTF8(keyEvent->key);
    }
#if DEBUGPRINT_KEYBOARD
    printf(
            "%d key: %s, code: %s, ctrl: %d, shift: %d, alt: %d, meta: %d, repeat: %d, which: %lu\n",
            eventType,
            keyEvent->key,
            keyEvent->code,
            keyEvent->ctrlKey,
            keyEvent->shiftKey,
            keyEvent->altKey,
            keyEvent->metaKey,
            keyEvent->repeat,
            keyEvent->which
    );
#endif // DEBUGPRINT_KEYBOARD
    if(keyEvent->repeat)
    {
        return true;
    }
    io.KeyCtrl = keyEvent->ctrlKey;
    io.KeyShift = keyEvent->shiftKey;
    io.KeyAlt = keyEvent->altKey;
    io.KeySuper = keyEvent->metaKey;
    //io.KeySuper = false;

#if DEBUGPRINT_KEYBOARD
    printf("ctrl: %d, shift: %d, alt: %d, meta: %d\n",
        keyEvent->ctrlKey,
        keyEvent->shiftKey,
        keyEvent->altKey,
        keyEvent->metaKey
    );
#endif // DEBUGPRINT_KEYBOARD


    switch(eventType)
    {
    case EMSCRIPTEN_EVENT_KEYDOWN:
        {
            io.KeysDown[keyEvent->which] = 1;
        }
        break;
    case EMSCRIPTEN_EVENT_KEYUP:
        {
            io.KeysDown[keyEvent->which] = 0;
        }
        break;
    case EMSCRIPTEN_EVENT_KEYPRESS:
        {
            printf("%s was pressed\n", keyEvent->key);
        }
        break;
    }
    return handled;
}
