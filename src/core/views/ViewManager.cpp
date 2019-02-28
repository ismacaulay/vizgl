#include "ViewManager.h"

#include "I_Plot.h"
#include "I_RenderableRepository.h"
#include "I_View.h"
#include "I_ViewFactory.h"

ViewManager::ViewManager(
    I_ViewFactory& factory,
    I_RenderableRepository& repository,
    I_Plot& plot)
    : factory_(factory)
    , repository_(repository)
    , plot_(plot)
{
    (void)plot_;
}

void ViewManager::createMesh(const std::vector<float>& vertices)
{
    const auto* view = factory_.createMesh(vertices, glm::vec4(1.0, 0.0, 0.0, 1.0));
    plot_.containVertices(vertices);
    repository_.add(view);
}

void ViewManager::createMesh(const std::vector<float>& vertices, const std::vector<uint32_t>& indices)
{
    std::vector<float> positions(indices.size() * 3);
    for(int i = 0; i < indices.size(); i++) {
        auto index = indices[i];
        positions[(i * 3) + 0] = vertices[(index * 3) + 0];
        positions[(i * 3) + 1] = vertices[(index * 3) + 1];
        positions[(i * 3) + 2] = vertices[(index * 3) + 2];
    }

    createMesh(positions);
}

// mat4x4(
//     (0.000667, 0.000000, 0.000000, 0.000000),
//     (0.000000, 0.000667, 0.000000, 0.000000),
//     (0.000000, 0.000000, 0.000667, 0.000000),
//     (-445500.343750, -493500.687500, -2972.887695, 1.000000))
