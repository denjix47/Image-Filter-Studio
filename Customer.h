#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "User.h"
using namespace std;

class Customer : public User
{
private:
    string gender;
    string phone;
    string city;
    bool isBlocked;
    int sessionCount;

public:
    // Constructor
    Customer(string cnic, string pwd, string name, string gender, string phone, string city, bool isBlocked, int sessionCount);

    // Destructor
    ~Customer();

    void showMenu() override;

    // Getters / Setters for file management
    bool getIsBlocked() const;
    void setBlocked(bool status);
    int getSessionCount() const;
    void incrementSessionCount();
    string toFileString() const; // Helper to format data for customers.txt
};

#endif