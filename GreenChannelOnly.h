#ifndef GREENCHANNELONLY_H
#define GREENCHANNELONLY_H

#include "Filter.h"

class GreenChannelOnly : public Filter
{
public:
    GreenChannelOnly();

    void apply(Image &img) override;
};

#endif
