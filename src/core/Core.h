#pragma once
#include <memory>

#include "I_ViewApi.h"
#include "I_CameraApi.h"

class Core {
public:
    Core();
    ~Core();

    void setSize(int width, int height);

    void render();

    I_ViewApi& viewApi() const;
    I_CameraApi& cameraApi() const;

private:
    class Impl;
    std::unique_ptr<Impl> p_;
};
