#pragma once
#include <memory>

#include "I_CameraApi.h"
#include "I_ColorMapApi.h"
#include "I_GeometryApi.h"
#include "I_MappingApi.h"
#include "I_ModelApi.h"
#include "I_PlotApi.h"

class Core {
public:
    Core();
    ~Core();

    void setSize(int width, int height);

    void render();

    I_ColorMapApi& colorMapApi() const;
    I_GeometryApi& geometryApi() const;
    I_MappingApi& mappingApi() const;
    I_ModelApi& modelApi() const;

    // I_ViewApi& viewApi() const;
    I_CameraApi& cameraApi() const;
    I_PlotApi& plotApi() const;

private:
    class Impl;
    std::unique_ptr<Impl> p_;
};
