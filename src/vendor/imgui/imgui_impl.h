/* Ported from: https://github.com/hef/imgui-in-browser/ */
#pragma once

struct ImDrawData;
struct EmscriptenMouseEvent;
struct EmscriptenWheelEvent;
struct EmscriptenKeyboardEvent;

class ImGuiImpl {
public:
    static void init();
    static void BeginFrame();
private:
    static void initGraphics();
    static void initFont();
    static void RenderDrawLists(ImDrawData* drawData);
    static int mouseCallback(int eventType, const EmscriptenMouseEvent* mouseEvent, void* userData);
    static int wheelCallback(int eventType, const EmscriptenWheelEvent* wheelEvent, void* userData);
    static int keyboardCallback(int eventType, const EmscriptenKeyboardEvent* keyEvent, void* userData);
    static const char* vertexShader;
    static const char* fragmentShader;
    static int m_shaderHandle;
    static int m_texture;
    static int m_projectionMatrix;
    static int m_position;
    static int m_uv;
    static int m_color;
    static unsigned int m_vao;
    static unsigned int m_vbo;
    static unsigned int m_elements;
    static unsigned int m_fontTexture;
};
