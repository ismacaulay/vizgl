#include "CoreInstance.h"

#include <stdio.h>

std::unique_ptr<Core> CoreInstance::instance_ = nullptr;

Core& CoreInstance::getInstance()
{
    if (instance_ == nullptr) {
        CoreInstance::reset();
    }
    return *instance_;
}

void CoreInstance::reset() {
    instance_ = std::make_unique<Core>();
}
