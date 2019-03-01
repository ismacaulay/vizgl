#pragma once
#include "I_ModelFactory.h"

class ModelFactory : public I_ModelFactory
{
public:
    explicit ModelFactory() = default;
    ~ModelFactory() = default;

    std::shared_ptr<I_Model> create(
        const IntegerId& geometryId,
        const IntegerId& shaderId,
        const IntegerId& mappingId);
};
