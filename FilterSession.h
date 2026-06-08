#ifndef FILTERSESSION_H
#define FILTERSESSION_H

#include <vector>
#include <string>
#include "Image.h"
#include "Filter.h"
using namespace std;

// Forward declaration of Customer to avoid circular dependencies for now
class Customer; 

class FilterSession {
private:
    Customer* customer;
    Image* image;
    vector<Filter*> pipeline;
    string timestamp;

public:
    // Constructor
    FilterSession(Customer* cust, Image* img);
    
    // Destructor
    ~FilterSession();

    // Pipeline management
    FilterSession& addFilter(Filter* f); // Returns reference to allow method chaining!
    void clearPipeline();
    void applyAll(Image& img);
    
    // Output
    void saveResult(string path);
};

#endif 