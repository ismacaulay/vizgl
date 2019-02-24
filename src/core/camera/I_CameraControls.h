#pragma once

class I_CameraControls
{
public:
    virtual ~I_CameraControls() {}

    virtual void startRotate(double x, double y) = 0;
    virtual void startPan(double x, double y) = 0;
    virtual void move(double x, double y) = 0;
    virtual void zoom(double delta) = 0;
    virtual void finish() = 0;
};
