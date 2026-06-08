#include "Pixel.h"

//default constructor
Pixel::Pixel()
{
    this->r = 0;
    this->g = 0;
    this->b = 0;
}

//parameterized constructor
Pixel::Pixel(int r, int g, int b)
{
    this->r = clamp(r);
    this->g = clamp(g);
    this->b = clamp(b);
}

int Pixel::clamp(int value)
{
    if (value < 0)
        return 0;
    if (value > 255)
        return 255;
    return value;
}

//getters
int Pixel::getR() const { return r; }
int Pixel::getG() const { return g; }
int Pixel::getB() const { return b; }

//setters
void Pixel::setR(int r) { this->r = clamp(r); }
void Pixel::setG(int g) { this->g = clamp(g); }
void Pixel::setB(int b) { this->b = clamp(b); }

// Calculate average brightness 
int Pixel::getBrightness() const
{
    return (r + g + b) / 3;
}

// Pixel brightness to ASCII character
char Pixel::toASCIIChar() const
{
    int brightness = getBrightness();

    if (brightness < 50)
        return '.';
    if (brightness < 100)
        return ':';
    if (brightness < 150)
        return '+';
    if (brightness < 200)
        return '*';
    return '@';
}

// Operator overloading for pixel addition
Pixel Pixel::operator+(const Pixel &other) const
{
    return Pixel(
        clamp(r + other.r),
        clamp(g + other.g),
        clamp(b + other.b));
}

// Overloading the stream insertion operator for easy output
std::ostream &operator<<(std::ostream &os, const Pixel &pixel)
{
    os << pixel.toASCIIChar();
    return os;
}
