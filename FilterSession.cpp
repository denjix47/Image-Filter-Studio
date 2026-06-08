#include "FilterSession.h"
#include <iostream>
#include <ctime>
using namespace std;

// Constructor
FilterSession::FilterSession(Customer *cust, Image *img)
{
    this->customer = cust;
    this->image = img;

    // Generate the real, live timestamp for this session
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char timeBuf[32];
    snprintf(timeBuf, sizeof(timeBuf), "%04d%02d%02d_%02d%02d%02d",1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday,ltm->tm_hour, ltm->tm_min, ltm->tm_sec);

    this->timestamp = string(timeBuf); 
}

// Destructor
FilterSession::~FilterSession()
{
    clearPipeline();
}

// Method Chaining: Returns a reference to the session itself
FilterSession &FilterSession::addFilter(Filter *f)
{
    this->pipeline.push_back(f);
    return *this;
}

// Clears the vector and frees the dynamically allocated filters
void FilterSession::clearPipeline()
{
    for (int i = 0; i < this->pipeline.size(); i++)
    {
        delete this->pipeline[i];
    }
    this->pipeline.clear();
}

// The core engine: runs the image through every filter in the vector
void FilterSession::applyAll(Image &img)
{
    cout << "=== Applying Pipeline ===\n";

    for (int i = 0; i < this->pipeline.size(); i++)
    {
        // Polymorphism in action! The virtual apply() method is called.
        if (this->pipeline[i]->isEnabled())
        {
            cout << "Applying filter " << (i + 1) << "/" << this->pipeline.size()
                 << ": " << this->pipeline[i]->getName() << "\n";

            this->pipeline[i]->apply(img);

            // Show ASCII preview after each filter step
            img.displayASCII();
        }
    }
    cout << "All filters applied.\n";
}

// Wrapper to save the result
void FilterSession::saveResult(string path)
{
    if (this->image != nullptr)
    {
        this->image->saveToFile(path);
    }
}

