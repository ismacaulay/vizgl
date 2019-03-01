#pragma once
#include "I_Plot.h"
#include "I_PlotApi.h"

class Plot : public I_Plot, public I_PlotApi
{
public:
    explicit Plot();
    ~Plot() = default;

    void setRotation(const glm::vec3& rotation);

    void contain(const BoundingBox& boundingBox);
    void containVertices(const std::vector<float>& vertices);

    const glm::mat4& model() const;

private:
    void updateMatrix();

private:
    glm::vec2 xLimits_;
    glm::vec2 yLimits_;
    glm::vec2 zLimits_;

    glm::mat4 model_;

    glm::vec3 rotation_;
};
