#pragma once
#include "I_Geometry.h"

class IntegerId;

class I_VoxelGeometry : public I_Geometry
{
public:
    virtual ~I_VoxelGeometry() = default;

    virtual const IntegerId& id() const = 0;
};
