#include "Model.h"

Model::Model(
    IntegerId geometryId,
    IntegerId shaderId,
    IntegerId mappingId)
    : geometryId_(geometryId)
    , shaderId_(shaderId)
    , mappingId_(mappingId)
{
}

const IntegerId& Model::geometryId() const
{
    return geometryId_;
}

const IntegerId& Model::shaderId() const
{
    return shaderId_;
}

const IntegerId& Model::mappingId() const
{
    return mappingId_;
}
