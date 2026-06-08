#ifndef BLUECHANNELONLY_H
#define BLUECHANNELONLY_H

#include "Filter.h"

class BlueChannelOnly : public Filter
{
public:
    BlueChannelOnly();

    void apply(Image &img) override;
};

#endif
