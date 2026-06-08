#ifndef INVERT_H
#define INVERT_H

#include "Filter.h"

class Invert : public Filter
{
public:
    Invert();

    void apply(Image &img) override;
};

#endif
