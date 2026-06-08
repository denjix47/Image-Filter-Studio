#include "ContrastStretch.h"

// Intialize base class metadata
ContrastStretch::ContrastStretch() : Filter(4, "Contrast Stretch", "Pixel Transform") {}

// Contrast stretch logic
void ContrastStretch::apply(Image &img)
{
    // 1. Initialize variables to find the min and max for each channel
    int minR = 255, maxR = 0;
    int minG = 255, maxG = 0;
    int minB = 255, maxB = 0;

    // 2. First Pass: Find the actual minimums and maximums
    for (int row = 0; row < img.getHeight(); row++)
    {
        for (int col = 0; col < img.getWidth(); col++)
        {
            Pixel &p = img.at(row, col);

            if (p.getR() < minR)
                minR = p.getR();
            if (p.getR() > maxR)
                maxR = p.getR();

            if (p.getG() < minG)
                minG = p.getG();
            if (p.getG() > maxG)
                maxG = p.getG();

            if (p.getB() < minB)
                minB = p.getB();
            if (p.getB() > maxB)
                maxB = p.getB();
        }
    }

    // 3. Second Pass: Apply the contrast stretch formula
    for (int row = 0; row < img.getHeight(); row++)
    {
        for (int col = 0; col < img.getWidth(); col++)
        {
            Pixel &p = img.at(row, col);

            // Avoid division by zero if max == min
            if (maxR > minR)
            {
                int newR = ((p.getR() - minR) * 255) / (maxR - minR);
                p.setR(newR);
            }
            if (maxG > minG)
            {
                int newG = ((p.getG() - minG) * 255) / (maxG - minG);
                p.setG(newG);
            }
            if (maxB > minB)
            {
                int newB = ((p.getB() - minB) * 255) / (maxB - minB);
                p.setB(newB);
            }
        }
    }
}