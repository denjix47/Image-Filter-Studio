#ifndef BRIGHTNESSADJUST_H
#define BRIGHTNESSADJUST_H

#include "Filter.h"

class BrightnessAdjust : public Filter {
private:
    int amount; 

public:
    BrightnessAdjust(int amount);
    void apply(Image& img) override;
};

#endif