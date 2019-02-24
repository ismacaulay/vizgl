#include "MeshView.h"

#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"
#include "Shader.h"

namespace {
const unsigned int VERTEX_SIZE = 3;
const unsigned int COLOR_SIZE = 3;

const std::string VERTEX_SHADER = ""
"precision highp float;                                                     \n"
"attribute vec3 a_position;                                                 \n"
"attribute vec3 a_color;                                                    \n"
"                                                                           \n"
"uniform mat4 u_model;                                                      \n"
"uniform mat4 u_view;                                                       \n"
"uniform mat4 u_proj;                                                       \n"
"                                                                           \n"
"varying vec4 v_color;                                                      \n"
"                                                                           \n"
"void main() {                                                              \n"
"   gl_Position = u_proj * u_view * u_model * vec4(a_position, 1.0);        \n"
"   v_color = vec4(a_color, 1.0);                                           \n"
"}                                                                          \n";

const std::string FRAGMENT_SHADER = ""
"precision highp float;             \n"
"varying vec4 v_color;              \n"
"                                   \n"
"void main() {                      \n"
"   gl_FragColor = v_color;         \n"
"}                                  \n";

}

class MeshView::Impl
{
public:
    Impl(const std::vector<float>& vertices)
        : vb(vertices.data(), vertices.size() * (VERTEX_SIZE + COLOR_SIZE) * sizeof(float))
        , layout()
        , va()
        , shader(VERTEX_SHADER, FRAGMENT_SHADER)
    {
        layout.push<float>(VERTEX_SIZE);
        layout.push<float>(COLOR_SIZE);

        va.addBuffer(vb, layout);
    }

    VertexBuffer vb;
    VertexBufferLayout layout;
    VertexArray va;
    Shader shader;
};

MeshView::MeshView(const std::vector<float>& vertices)
    : p_(std::make_unique<Impl>(vertices))
{
}

const VertexArray& MeshView::vertexArray() const
{
    return p_->va;
}

const VertexBuffer& MeshView::vertexBuffer() const
{
    return p_->vb;
}

Shader& MeshView::shader() const
{
    return p_->shader;
}
