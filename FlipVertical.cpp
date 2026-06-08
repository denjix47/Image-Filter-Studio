#include "FlipVertical.h"

// Initialize base class metadata
FlipVertical::FlipVertical() : Filter(10, "Flip Vertical", "Geometric") {}

// Flip vertical filter logic
void FlipVertical::apply(Image &img)
{
    // Only go halfway down the height!
    for (int row = 0; row < img.getHeight() / 2; row++)
    {
        for (int col = 0; col < img.getWidth(); col++)
        {
            Pixel &topPixel = img.at(row, col);
            Pixel &bottomPixel = img.at(img.getHeight() - 1 - row, col);

            // Swap their values
            Pixel temp = topPixel;
            topPixel = bottomPixel;
            bottomPixel = temp;
        }
    }
}