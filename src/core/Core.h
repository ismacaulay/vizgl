#pragma once
#include <memory>

#include "ViewManager.h"
#include "CameraController.h"

class Core {
public:
    Core();
    ~Core();

    void setSize(int width, int height);

    void run();

    ViewManager& viewManager() const;
    CameraController& cameraController() const;

private:
    class Impl;
    std::unique_ptr<Impl> p_;
};
