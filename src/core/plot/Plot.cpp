#include "Plot.h"

#include <glm/gtc/matrix_transform.hpp>

#include <stdio.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

Plot::Plot()
    : xLimits_(std::numeric_limits<float>::max(), std::numeric_limits<float>::min())
    , yLimits_(std::numeric_limits<float>::max(), std::numeric_limits<float>::min())
    , zLimits_(std::numeric_limits<float>::max(), std::numeric_limits<float>::min())
    , model_(1.0f)
{
}

void Plot::containVertices(const std::vector<float>& vertices)
{
    float min_x = std::numeric_limits<float>::max();
    float max_x = std::numeric_limits<float>::min();

    float min_y = std::numeric_limits<float>::max();
    float max_y = std::numeric_limits<float>::min();

    float min_z = std::numeric_limits<float>::max();
    float max_z = std::numeric_limits<float>::min();

    for (int i = 0; i < vertices.size() / 3; i++) {
        float x = vertices[(i * 3) + 0];
        float y = vertices[(i * 3) + 1];
        float z = vertices[(i * 3) + 2];

        min_x = std::min(x, min_x);
        max_x = std::max(x, max_x);

        min_y = std::min(y, min_y);
        max_y = std::max(y, max_y);

        min_z = std::min(z, min_z);
        max_z = std::max(z, max_z);
    }

    xLimits_.x = std::min(xLimits_.x, min_x);
    xLimits_.y = std::max(xLimits_.y, max_x);

    yLimits_.x = std::min(yLimits_.x, min_y);
    yLimits_.y = std::max(yLimits_.y, max_y);

    zLimits_.x = std::min(zLimits_.x, min_z);
    zLimits_.y = std::max(zLimits_.y, max_z);

    updateMatrix();
}

const glm::mat4& Plot::model() const
{
    return model_;
}

void Plot::updateMatrix()
{
    glm::vec3 t(
        xLimits_.x + (xLimits_.y - xLimits_.x)/2.0f,
        yLimits_.x + (yLimits_.y - yLimits_.x)/2.0f,
        zLimits_.x + (zLimits_.y - zLimits_.x)/2.0f
    );

    float diff_x = std::abs(xLimits_.y - xLimits_.x);
    float diff_y = std::abs(yLimits_.y - yLimits_.x);
    float diff_z = std::abs(zLimits_.y - zLimits_.x);
    float scale = std::max(diff_x, std::max(diff_y, diff_z));
    glm::vec3 s(scale);

    glm::mat4 matrix(1.0f);
    matrix = glm::scale(matrix, 2.0f/s);
    matrix = glm::translate(matrix, -t);

    printf("[xLimits] %s\n", glm::to_string(xLimits_).c_str());
    printf("[yLimits] %s\n", glm::to_string(yLimits_).c_str());
    printf("[zLimits] %s\n", glm::to_string(zLimits_).c_str());
    printf("[scale] %f\n", scale);
    printf("[t] %s\n", glm::to_string(-t).c_str());
    printf("[s] %s\n", glm::to_string(2.0f/s).c_str());
    printf("[matrix] %s\n", glm::to_string(matrix).c_str());
    model_ = matrix;
}
