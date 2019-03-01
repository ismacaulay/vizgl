#pragma once
#include "I_Model.h"

#include "IntegerId.h"

class Model : public I_Model
{
public:
    explicit Model(
        IntegerId geometryId,
        IntegerId shaderId,
        IntegerId mappingId);
    ~Model() = default;

    const IntegerId& geometryId() const;
    const IntegerId& shaderId() const;
    const IntegerId& mappingId() const;

private:
    IntegerId geometryId_;
    IntegerId shaderId_;
    IntegerId mappingId_;
};
