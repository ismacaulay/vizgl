#pragma once
#include "I_Plot.h"

class Plot : public I_Plot
{
public:
    explicit Plot();
    ~Plot() = default;

    void containVertices(const std::vector<float>& vertices);

    const glm::mat4& model() const;

private:
    void updateMatrix();

private:
    glm::vec2 xLimits_;
    glm::vec2 yLimits_;
    glm::vec2 zLimits_;

    glm::mat4 model_;
};
