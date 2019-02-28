#pragma once

#include "I_ViewFactory.h"

class I_View;

class ViewFactory : public I_ViewFactory
{
public:
    ViewFactory() = default;
    ~ViewFactory() = default;

    I_View* createMesh(
        const std::vector<float>& vertices,
        const glm::vec4& color);
};
