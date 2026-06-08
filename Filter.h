#ifndef FILTER_H
#define FILTER_H

#include <string>
#include "Image.h"

class Filter
{
protected:
    int id;
    string name;
    string category;
    bool enabled;

public:
    Filter(int id, string name, string category);

    virtual ~Filter();

    // Pure virtual function to apply the filter to an image
    virtual void apply(Image &img) = 0;

    // Getters
    int getID() const;
    string getName() const;
    string getCategory() const;
    bool isEnabled() const;

    // Toggles the enabled state of the filter
    void toggle();
};

#endif // FILTER_H