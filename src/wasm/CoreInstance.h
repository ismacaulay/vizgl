#pragma once
#include <memory>
#include "Core.h"

class CoreInstance
{
public:
    static Core& getInstance();

private:
    CoreInstance();

    static std::shared_ptr<Core> instance_;
};
