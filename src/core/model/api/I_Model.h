#pragma once

class IntegerId;

class I_Model
{
public:
    virtual ~I_Model() = default;

    virtual const IntegerId& geometryId() const = 0;
    virtual const IntegerId& shaderId() const = 0;
    virtual const IntegerId& mappingId() const = 0;
};
