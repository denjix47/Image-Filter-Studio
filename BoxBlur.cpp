#include "BoxBlur.h"

// Initialize base class metadata
BoxBlur::BoxBlur() : Filter(8, "Box Blur (3x3)", "Spatial Filter") {}

// Box blur filter logic
void BoxBlur::apply(Image &img)
{
    // Create a copy to read from (This relies on the Copy Constructor!)
    Image copyImg = img;

    for (int row = 0; row < img.getHeight(); row++)
    {
        for (int col = 0; col < img.getWidth(); col++)
        {

            int sumR = 0, sumG = 0, sumB = 0;
            int count = 0; // Keep track of how many neighbors exist

            // Loop through the 3x3 grid around the current pixel
            for (int dy = -1; dy <= 1; dy++)
            {
                for (int dx = -1; dx <= 1; dx++)
                {

                    int neighborRow = row + dy;
                    int neighborCol = col + dx;

                    // Bounds checking: only include pixels inside the image
                    if (neighborRow >= 0 && neighborRow < copyImg.getHeight() &&
                        neighborCol >= 0 && neighborCol < copyImg.getWidth())
                    {

                        // Read from the UNMODIFIED copy
                        Pixel &neighbor = copyImg.at(neighborRow, neighborCol);

                        sumR = sumR + neighbor.getR();
                        sumG = sumG + neighbor.getG();
                        sumB = sumB + neighbor.getB();
                        count++;
                    }
                }
            }

            // Calculate the average and write to the ORIGINAL image
            Pixel &p = img.at(row, col);
            p.setR(sumR / count);
            p.setG(sumG / count);
            p.setB(sumB / count);
        }
    }
}