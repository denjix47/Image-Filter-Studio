#ifndef FLIPHORIZONTAL_H
#define FLIPHORIZONTAL_H

#include "Filter.h"

class FlipHorizontal : public Filter
{
public:
    FlipHorizontal();

    void apply(Image &img) override;
};

#endif
