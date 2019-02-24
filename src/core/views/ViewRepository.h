#pragma once

#include "I_ViewRepository.h"

class ViewRepository : public I_ViewRepository
{
public:
    ViewRepository();
    virtual ~ViewRepository();

    void addView(I_View* view);
    const std::vector<const I_View*> allViews() const;

private:
    std::vector<I_View*> views_;
};
