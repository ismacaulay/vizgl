#pragma once
#include <memory>

class IntegerId;
class I_Model;

class I_ModelFactory
{
public:
    virtual ~I_ModelFactory() = default;

    virtual std::shared_ptr<I_Model> create(
        const IntegerId& geometryId,
        const IntegerId& shaderId,
        const IntegerId& mappingId) = 0;
};
