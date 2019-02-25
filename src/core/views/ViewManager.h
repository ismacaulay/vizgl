#pragma once
#include "I_ViewApi.h"

#include <vector>

class I_ViewFactory;
class I_RenderableRepository;

class ViewManager : public I_ViewApi
{
public:
    ViewManager(I_ViewFactory& factory, I_RenderableRepository& repository);
    virtual ~ViewManager() = default;

    void createMesh(const std::vector<float>& vertices);
    void createMesh(const std::vector<float>& vertices, const std::vector<uint32_t>& indices);

private:
    I_ViewFactory& factory_;
    I_RenderableRepository& repository_;
};
