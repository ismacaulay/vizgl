#pragma once

#include <vector>

class I_ViewFactory;
class I_ViewRepository;

class ViewManager
{
public:
    ViewManager(I_ViewFactory& factory, I_ViewRepository& repository);
    virtual ~ViewManager() = default;

    void createMesh(const std::vector<float>& vertices);

private:
    I_ViewFactory& factory_;
    I_ViewRepository& repository_;
};
