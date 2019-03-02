#pragma once
#include "I_ColorMapApi.h"

class I_ColorMapFactory;
template<typename T> class I_Repository;
class I_ColorMap;

class ColorMapManager : public I_ColorMapApi
{
public:
    explicit ColorMapManager(I_ColorMapFactory& factory, I_Repository<I_ColorMap>& repository);

    IntegerId createColorMap(const std::vector<unsigned char>& colors);

private:
    I_ColorMapFactory& factory_;
    I_Repository<I_ColorMap>& repository_;
};
