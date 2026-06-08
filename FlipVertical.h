#ifndef FLIPVERTICAL_H
#define FLIPVERTICAL_H

#include "Filter.h"

class FlipVertical : public Filter
{
public:
    FlipVertical();

    void apply(Image &img) override;
};

#endif
