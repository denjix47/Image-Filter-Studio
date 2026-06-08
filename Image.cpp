#include "Image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
using namespace std;

// Displays ASCII in the terminal
void Image::displayASCII() const
{
    cout << "=== ASCII Preview (" << this->width << "x" << this->height << ") ===" << endl;

    // Limit display size to prevent flooding the terminal

    int displayHeight = (this->height > 10) ? 10 : this->height;
    int displayWidth = (this->width > 40) ? 40 : this->width;

    for (int row = 0; row < displayHeight; row++)
    {
        for (int col = 0; col < displayWidth; col++)
        {
            cout << this->grid[row][col];
        }
        cout << endl;
    }

    if (this->height > 10 || this->width > 40)
    {
        cout << "(truncated for display)\n";
    }
}

Image::Image()
{
    this->width = 5;
    this->height = 5;

    this->grid = new Pixel *[this->height];

    for (int i = 0; i < this->height; i++)
    {
        this->grid[i] = new Pixel[this->width];
    }
}

// Destructor: Frees DMA of grid
Image::~Image()
{
    if (this->grid != nullptr)
    {

        for (int i = 0; i < this->height; i++)
        {
            delete[] this->grid[i];
        }

        delete[] this->grid;

        this->grid = nullptr;
    }
}

// Getters for dimensions
int Image::getWidth() const { return this->width; }
int Image::getHeight() const { return this->height; }

// Access pixel at (row, col)
Pixel &Image::at(int row, int col)
{
    return this->grid[row][col];
}

// Deep copy constructor
Image::Image(const Image &other)
{
    this->width = other.getWidth();
    this->height = other.getHeight();

    // 1. Allocate a brand new grid on the heap
    this->grid = new Pixel *[this->height];
    for (int i = 0; i < this->height; i++)
    {
        this->grid[i] = new Pixel[this->width];
    }

    // 2. Loop through and copy every pixel's exact values over
    for (int row = 0; row < this->height; row++)
    {
        for (int col = 0; col < this->width; col++)
        {
            int r = other.grid[row][col].getR();
            int g = other.grid[row][col].getG();
            int b = other.grid[row][col].getB();

            this->grid[row][col].setR(r);
            this->grid[row][col].setG(g);
            this->grid[row][col].setB(b);
        }
    }
}

// File loading using stb_image library
bool Image::loadFromFile(string path)
{
    int w, h, channels;

    // stbi_load takes the path, passes dimensions by reference to fill them, and the '3' forces it to load Red, Green, Blue channels

    unsigned char *raw_pixels = stbi_load(path.c_str(), &w, &h, &channels, 3);

    if (raw_pixels == nullptr)
    {
        cout << "Error: Could not load image at " << path << "\n";
        return false;
    }

    // 1. CLEANUP:Image object already holds a grid (like the 5x5 one), delete it first before making a new one to prevent memory leaks!

    if (this->grid != nullptr)
    {
        for (int i = 0; i < this->height; i++)
        {
            delete[] this->grid[i];
        }
        delete[] this->grid;
    }

    // 2. Update dimensions to match the loaded image
    this->width = w;
    this->height = h;

    // 3. ALLOCATE: Create the new 2D grid with the real image dimensions
    this->grid = new Pixel *[this->height];
    for (int i = 0; i < this->height; i++)
    {
        this->grid[i] = new Pixel[this->width];
    }

    // 4. POPULATE: Copy the data from the library's 1D array into our 2D grid
    for (int row = 0; row < this->height; row++)
    {
        for (int col = 0; col < this->width; col++)
        {

            // Math magic to find the 1D index for a 2D coordinate
            int index = 3 * (row * this->width + col);

            int r = raw_pixels[index + 0]; // Red
            int g = raw_pixels[index + 1]; // Green
            int b = raw_pixels[index + 2]; // Blue

            this->grid[row][col].setR(r);
            this->grid[row][col].setG(g);
            this->grid[row][col].setB(b);
        }
    }

    // 5. FREE MEMORY

    stbi_image_free(raw_pixels);

    return true;
}

// File saving
void Image::saveToFile(string path)
{
    // 1. Allocate a temporary 1D array to hold the raw bytes
    // Total size = width * height * 3 (for R, G, B channels)
    unsigned char *raw_pixels = new unsigned char[this->width * this->height * 3];

    // 2. Flatten our 2D grid back into the 1D array
    for (int row = 0; row < this->height; row++)
    {
        for (int col = 0; col < this->width; col++)
        {
            int index = 3 * (row * this->width + col);

            raw_pixels[index + 0] = this->grid[row][col].getR();
            raw_pixels[index + 1] = this->grid[row][col].getG();
            raw_pixels[index + 2] = this->grid[row][col].getB();
        }
    }

    // 3. Write the raw pixel data to a PNG file using stb_image_write
    // The last parameter is the "stride" in bytes (width * 3 channels).
    stbi_write_png(path.c_str(), this->width, this->height, 3, raw_pixels, this->width * 3);

    // 4. Free the temporary raw pixel array to prevent memory leaks
    delete[] raw_pixels;
}