#include "RedChannelOnly.h"

// Initialize base class metadata
RedChannelOnly::RedChannelOnly() : Filter(5, "Red Channel Only", "Pixel Transform") {}

// Red channel only filter logic
void RedChannelOnly::apply(Image &img)
{
    for (int row = 0; row < img.getHeight(); row++)
    {
        for (int col = 0; col < img.getWidth(); col++)
        {
            Pixel &p = img.at(row, col);
            p.setG(0); // Turn off Green
            p.setB(0); // Turn off Blue
        }
    }
}