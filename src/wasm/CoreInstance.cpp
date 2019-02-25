#include "CoreInstance.h"

std::shared_ptr<Core> CoreInstance::instance_ = nullptr;

Core& CoreInstance::getInstance()
{
    if (instance_ == nullptr) {
        instance_ = std::make_shared<Core>();
    }
    return *instance_;
}
