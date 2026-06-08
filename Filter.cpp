#include "Filter.h"

// Parameterized constructor
Filter::Filter(int id, string name, string category)
{
    this->id = id;
    this->name = name;
    this->category = category;
    this->enabled = true;
}

// Destructor
Filter::~Filter() {}

// Getters
int Filter::getID() const { return this->id; }
string Filter::getName() const { return this->name; }
string Filter::getCategory() const { return this->category; }
bool Filter::isEnabled() const { return this->enabled; }

// Toggle function 
void Filter::toggle()
{
    if (this->enabled)
    {
        this->enabled = false;
    }
    else
    {
        this->enabled = true;
    }
}