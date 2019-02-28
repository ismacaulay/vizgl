#pragma once
#include <memory>
#include "Core.h"

class CoreInstance
{
public:
    static Core& getInstance();

private:
    CoreInstance();

    static std::unique_ptr<Core> instance_;
};
