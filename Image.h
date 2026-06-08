#ifndef IMAGE_H
#define IMAGE_H
#include "Pixel.h"
#include <iostream>
#include <string>
using namespace std;

class Displayable
{
public:
    virtual void displayASCII() const = 0;
    virtual ~Displayable() {}
};

class Saveable
{
public:
    virtual void saveToFile(string path) = 0;
    virtual ~Saveable() {}
};

class Image : public Displayable, public Saveable
{
private:
    int width;
    int height;
    Pixel **grid;

public:
    friend class FilterSession;
    Image();
    Image(const Image &other);
    ~Image();

    // Core Access Methods
    Pixel &at(int row, int col);
    int getWidth() const;
    int getHeight() const;

    // File I/O & Display
    bool loadFromFile(string path);
    void saveToFile(string path) override;
    void displayASCII() const override;

};

#endif