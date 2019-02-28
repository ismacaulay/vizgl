#pragma once
#include <memory>

class Core;

class ImGuiCore
{
public:
    explicit ImGuiCore(const Core& core);
    ~ImGuiCore();

    void render();

private:
    class Impl;
    std::unique_ptr<Impl> p_;
};
