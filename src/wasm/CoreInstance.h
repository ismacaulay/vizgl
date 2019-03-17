#pragma once
#include <memory>
#include "Core.h"

class CoreInstance
{
public:
    static Core& getInstance();

    static void reset();

private:
    CoreInstance();

    static std::unique_ptr<Core> instance_;
};
