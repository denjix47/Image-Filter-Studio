#include "Grayscale.h"

// Intialize base class metadata
Grayscale::Grayscale() : Filter(1, "Grayscale", "Pixel Transform") {}

// Grayscale filter logic
void Grayscale::apply(Image &img)
{
    for (int row = 0; row < img.getHeight(); row++)
    {
        for (int col = 0; col < img.getWidth(); col++)
        {

            // Get a reference to the current pixel using the at() method
            Pixel &currentPixel = img.at(row, col);

            // Calculate the average (R+G+B)/3
            int avg = currentPixel.getBrightness();

            // Set all channels to the average to make it gray
            currentPixel.setR(avg);
            currentPixel.setG(avg);
            currentPixel.setB(avg);
        }
    }
}