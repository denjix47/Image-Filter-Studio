#ifndef REDCHANNELONLY_H
#define REDCHANNELONLY_H
#include "Filter.h"

class RedChannelOnly : public Filter
{
public:
    RedChannelOnly();

    void apply(Image &img) override;
};

#endif
