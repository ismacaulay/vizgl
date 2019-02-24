#pragma once

#include <memory>
#include <vector>

class I_View;

class I_ViewFactory
{
public:
    virtual ~I_ViewFactory() = default;

    virtual I_View* createMesh(const std::vector<float>& vertices) = 0;
};
