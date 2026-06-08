#ifndef CUSTOMERMANAGER_H
#define CUSTOMERMANAGER_H

#include <string>
#include <vector>
#include "Customer.h"

using namespace std;

class CustomerManager
{
private:
    string FILENAME;

    // We store the loaded customers in a vector so we can easily search them
    vector<Customer> customerList;

public:
    CustomerManager();

    // Core File I/O
    void load();
    void save();

    // Search functions (returns a pointer so it can return nullptr if not found)
    Customer *searchByCNIC(string cnic);
    Customer *searchByName(string name);

    // Admin management functions
    void block(string cnic);
    void deleteCustomer(string cnic);
    bool isBlockedCNIC(string cnic);

    // Add a new customer to the list 
    void addCustomer(const Customer &c);
};

#endif // CUSTOMERMANAGER_H