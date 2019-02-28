#pragma once
#include <glm/glm.hpp>

class I_PlotApi;
template<typename T>
class ObservableValue;

class PlotController
{
public:
    explicit PlotController(I_PlotApi& api, ObservableValue<glm::vec3>& entity);
    ~PlotController() = default;
};
