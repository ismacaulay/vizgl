#include "ImGuiCoreInstance.h"
#include "CoreInstance.h"

std::unique_ptr<ImGuiCore> ImGuiCoreInstance::instance_ = nullptr;

ImGuiCore& ImGuiCoreInstance::getInstance()
{
    if (instance_ == nullptr) {
        instance_ = std::make_unique<ImGuiCore>(CoreInstance::getInstance());
    }
    return *instance_;
}
