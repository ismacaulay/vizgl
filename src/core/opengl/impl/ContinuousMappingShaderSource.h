#pragma once
#include <string>

namespace ContinuousMappingShaderSource {

const std::string VertexShader = ""
"precision highp float;                                                     \n"
"attribute vec3 a_position;                                                 \n"
"attribute float a_data;                                                    \n"
"                                                                           \n"
"uniform mat4 u_model;                                                      \n"
"uniform mat4 u_view;                                                       \n"
"uniform mat4 u_proj;                                                       \n"
"                                                                           \n"
"varying float v_data;                                                      \n"
"                                                                           \n"
"void main() {                                                              \n"
"   gl_Position = u_proj * u_view * u_model * vec4(a_position, 1.0);        \n"
"   v_data = a_data;                                                        \n"
"}                                                                          \n";

const std::string FragmentShader = ""
"precision highp float;                                                     \n"
"varying float v_data;                                                      \n"
"                                                                           \n"
"uniform float u_data_min;                                                  \n"
"uniform float u_data_max;                                                  \n"
"uniform sampler2D u_texture0;                                              \n"

"void main() {                                                              \n"
"   float x = (v_data - u_data_min) / (u_data_max - u_data_min);            \n"
"   x = clamp(x, 0.0, 1.0);                                                 \n"
"   gl_FragColor = texture2D(u_texture0, vec2(x, 0.5));                     \n"
"}                                                                          \n";

}
