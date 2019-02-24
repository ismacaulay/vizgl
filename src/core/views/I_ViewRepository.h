#pragma once

#include <vector>
#include <memory>

class I_View;

class I_ViewRepository
{
public:
    virtual ~I_ViewRepository() = default;

    virtual void addView(I_View* view) = 0;
    virtual const std::vector<const I_View*> allViews() const = 0;
};
