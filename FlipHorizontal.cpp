#include "FlipHorizontal.h"

// Initialize base class metadata
FlipHorizontal::FlipHorizontal() : Filter(9, "Flip Horizontal", "Geometric") {}

// Flip horizontal filter logic
void FlipHorizontal::apply(Image &img)
{
    for (int row = 0; row < img.getHeight(); row++)
    {
        // Only go halfway across the width!
        for (int col = 0; col < img.getWidth() / 2; col++)
        {
            Pixel &leftPixel = img.at(row, col);
            Pixel &rightPixel = img.at(row, img.getWidth() - 1 - col);

            // Swap their values
            Pixel temp = leftPixel;
            leftPixel = rightPixel;
            rightPixel = temp;
        }
    }
}
