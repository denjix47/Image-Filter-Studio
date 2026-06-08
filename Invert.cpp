#include "Invert.h"

// Initialize base class metadata
Invert::Invert() : Filter(2, "Invert / Negative", "Pixel Transform") {}

// Invert filter logic
void Invert::apply(Image &img)
{
    for (int row = 0; row < img.getHeight(); row++)
    {
        for (int col = 0; col < img.getWidth(); col++)
        {
            Pixel &p = img.at(row, col);

            // Subtract current color from 255 to invert it
            p.setR(255 - p.getR());
            p.setG(255 - p.getG());
            p.setB(255 - p.getB());
        }
    }
}