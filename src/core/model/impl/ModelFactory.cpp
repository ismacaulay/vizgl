#include "ModelFactory.h"

#include "Model.h"

std::shared_ptr<I_Model> ModelFactory::create(
        const IntegerId& geometryId,
        const IntegerId& shaderId,
        const IntegerId& mappingId)
{
    return std::make_shared<Model>(geometryId, shaderId, mappingId);
}
