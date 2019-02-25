#pragma once
#include <cstdint>
#include <vector>

class I_ViewApi
{
public:
    virtual ~I_ViewApi(){}

    virtual void createMesh(const std::vector<float>& vertices) = 0;
    virtual void createMesh(const std::vector<float>& vertices, const std::vector<uint32_t>& indices) = 0;
};
