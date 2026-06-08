#include "BlueChannelOnly.h"

// Initialize base class metadata
BlueChannelOnly::BlueChannelOnly() : Filter(7, "Blue Channel Only", "Pixel Transform") {}

// Blue channel only filter logic
void BlueChannelOnly::apply(Image &img)
{
    for (int row = 0; row < img.getHeight(); row++)
    {
        for (int col = 0; col < img.getWidth(); col++)
        {
            Pixel &p = img.at(row, col);
            p.setR(0); // Turn off Red
            p.setG(0); // Turn off Green
        }
    }
}