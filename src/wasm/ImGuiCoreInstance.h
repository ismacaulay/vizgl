#pragma once
#include <memory>
#include "ImGuiCore.h"

class ImGuiCoreInstance
{
public:
    static ImGuiCore& getInstance();

private:
    ImGuiCoreInstance();

    static std::unique_ptr<ImGuiCore> instance_;
};
