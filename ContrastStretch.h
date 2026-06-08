#ifndef CONTRASTSTRETCH_H
#define CONTRASTSTRETCH_H

#include "Filter.h"

class ContrastStretch : public Filter
{
public:
    ContrastStretch();
    void apply(Image &img) override;
};

#endif