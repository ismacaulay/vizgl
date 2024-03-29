#pragma once
#include "I_Mapping.h"

#include <memory>
#include <vector>

template<typename T> class I_Repository;
class I_ColorMap;
class IntegerId;

class ContinuousMapping : public I_Mapping
{
public:
    explicit ContinuousMapping(
        const std::vector<float>& data,
        I_Repository<I_ColorMap>& colorMapRepository,
        const IntegerId& gradientId,
        bool wireframe);
    ~ContinuousMapping();

    MappingType type() const;
    void bind(I_Shader& shader);

    void setGradient(const IntegerId& gradient);

private:
    class Impl;
    std::unique_ptr<Impl> p_;
};
