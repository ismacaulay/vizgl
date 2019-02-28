#include "PlotController.h"

#include "ObservableValue.h"
#include "I_PlotApi.h"

PlotController::PlotController(I_PlotApi& api, ObservableValue<glm::vec3>& entity)
{
    entity.onChanged([&api](const glm::vec3& value) {
        api.setRotation(value);
    });
}
