#ifndef GRAYSCALE_H
#define GRAYSCALE_H

#include "Filter.h"

class Grayscale : public Filter
{
public:
    Grayscale();

    void apply(Image &img) override;
};

#endif