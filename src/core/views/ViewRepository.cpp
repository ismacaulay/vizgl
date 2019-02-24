#include "ViewRepository.h"

#include "I_View.h"

ViewRepository::ViewRepository()
{
}
ViewRepository::~ViewRepository()
{
    for (I_View* v : views_) {
        delete v;
    }
}

void ViewRepository::addView(I_View* view)
{
    views_.push_back(view);
}

const std::vector<const I_View*> ViewRepository::allViews() const
{
    std::vector<const I_View*> views;
    for(I_View* v : views_) {
        views.push_back(v);
    }
    return views;
}
