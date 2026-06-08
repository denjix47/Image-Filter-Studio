#include "GreenChannelOnly.h"

// Initialize base class metadata
GreenChannelOnly::GreenChannelOnly() : Filter(6, "Green Channel Only", "Pixel Transform") {}

// Green channel only filter logic
void GreenChannelOnly::apply(Image &img)
{
    for (int row = 0; row < img.getHeight(); row++)
    {
        for (int col = 0; col < img.getWidth(); col++)
        {
            Pixel &p = img.at(row, col);
            p.setR(0); // Turn off Red
            p.setB(0); // Turn off Blue
        }
    }
}