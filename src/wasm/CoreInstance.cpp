#include "CoreInstance.h"

#include <stdio.h>

std::unique_ptr<Core> CoreInstance::instance_ = nullptr;

Core& CoreInstance::getInstance()
{
    if (instance_ == nullptr) {
        instance_ = std::make_unique<Core>();
    }
    return *instance_;
}
