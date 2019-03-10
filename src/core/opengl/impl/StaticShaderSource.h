#pragma once
#include <string>

namespace StaticShaderSource {

const std::string VertexShader = ""
"precision highp float;                                                     \n"
"attribute vec3 a_position;                                                 \n"
"                                                                           \n"
"uniform mat4 u_model;                                                      \n"
"uniform mat4 u_view;                                                       \n"
"uniform mat4 u_proj;                                                       \n"
"uniform vec3 u_color;                                                      \n"
"                                                                           \n"
"varying vec4 v_color;                                                      \n"
"                                                                           \n"
"void main() {                                                              \n"
"   gl_Position = u_proj * u_view * u_model * vec4(a_position, 1.0);        \n"
"   v_color = vec4(u_color, 1.0);                                           \n"
"}                                                                          \n";

const std::string FragmentShader = ""
"precision highp float;                                                     \n"
"varying vec4 v_color;                                                      \n"
"                                                                           \n"
"void main() {                                                              \n"
"   gl_FragColor = v_color;                                                 \n"
"}                                                                          \n";

const std::string VertexShader2 = ""
"precision highp float;                                                     \n"
"attribute vec3 a_position;                                                 \n"
"attribute vec3 a_barycentric;                                              \n"
"                                                                           \n"
"uniform mat4 u_model;                                                      \n"
"uniform mat4 u_view;                                                       \n"
"uniform mat4 u_proj;                                                       \n"
"                                                                           \n"
"varying vec3 v_barycentric;                                                \n"
"                                                                           \n"
"void main() {                                                              \n"
"   gl_Position = u_proj * u_view * u_model * vec4(a_position, 1.0);        \n"
"   v_barycentric = a_barycentric;                                          \n"
"}                                                                          \n";

const std::string FragmentShader2 = ""
"#extension GL_OES_standard_derivatives : enable                            \n"
"precision highp float;                                                     \n"
"                                                                           \n"
"varying vec3 v_barycentric;                                                \n"
"                                                                           \n"
"uniform vec3 u_color;                                                      \n"
"                                                                           \n"
"float edgeFactor() {                                                       \n"
"    vec3 d = fwidth(v_barycentric);                                        \n"
"    vec3 a3 = smoothstep(vec3(0.0), d*1.0, v_barycentric);                 \n"
"    return min(min(a3.x, a3.y), a3.z);                                     \n"
"}                                                                          \n"
"                                                                           \n"
"void main() {                                                              \n"
"   gl_FragColor = vec4(mix(vec3(0.0), u_color, edgeFactor()), 1.0);        \n"
"}                                                                          \n";

}
