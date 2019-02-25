#pragma once
#include <cstdint>
#include <vector>

class I_CameraApi
{
public:
    virtual ~I_CameraApi(){}

    virtual void start(int button, int x, int y) = 0;
    virtual void zoom(double delta) = 0;
    virtual void update(int x, int y) = 0;
    virtual void finish() = 0;
};
