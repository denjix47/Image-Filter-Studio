#include "BrightnessAdjust.h"

// Intialize base class metadata
BrightnessAdjust::BrightnessAdjust(int amount) : Filter(3, "Brightness Adjust", "Pixel Transform")
{
    this->amount = amount;
}

// Brightness adjustment logic
void BrightnessAdjust::apply(Image &img)
{
    for (int row = 0; row < img.getHeight(); row++)
    {
        for (int col = 0; col < img.getWidth(); col++)
        {
            Pixel &p = img.at(row, col);

            p.setR(p.getR() + this->amount);
            p.setG(p.getG() + this->amount);
            p.setB(p.getB() + this->amount);
        }
    }
}