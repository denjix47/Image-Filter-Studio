#ifndef PIXEL_H
#define PIXEL_H
#include <iostream>

class Pixel
{
private:
    int r;
    int g;
    int b;

public:
    Pixel();
    Pixel(int r, int g, int b);

    int getR() const;
    int getG() const;
    int getB() const;

    void setR(int r);
    void setG(int g);
    void setB(int b);

    int getBrightness() const;
    char toASCIIChar() const;
    static int clamp(int value);

    Pixel operator+(const Pixel &other) const;
    friend std::ostream &operator<<(std::ostream &os, const Pixel &pixel);
};

#endif
