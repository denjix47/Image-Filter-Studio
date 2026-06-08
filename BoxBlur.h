#ifndef BOXBLUR_H
#define BOXBLUR_H

#include "Filter.h"

class BoxBlur : public Filter
{
public:
    BoxBlur();
    void apply(Image &img) override;
};

#endif