#include "Customer.h"
#include <iostream>
using namespace std;

// Parameterized constructor
Customer::Customer(string cnic, string pwd, string name, string gender, string phone, string city, bool isBlocked, int sessionCount) : User(cnic, pwd, name)
{
    this->gender = gender;
    this->phone = phone;
    this->city = city;
    this->isBlocked = isBlocked;
    this->sessionCount = sessionCount;
    cout << "[System] Customer derived copy created.\n";
}

// Destructor
Customer::~Customer()
{
    cout << "[System] Customer derived destroyed.\n";
}

// Customer menu
void Customer::showMenu()
{
    cout << "\n=== Welcome, " << this->fullName << " ===\n";
    cout << "Sessions completed: " << this->sessionCount << "\n";
    cout << "1. Browse Filter Catalog\n";
    cout << "2. Load Image\n";
    cout << "3. Build Filter Pipeline\n";
    cout << "4. Apply Pipeline & Save Result\n";
    cout << "5. View My Session History\n";
    cout << "6. Logout\n";
    cout << "Your choice: ";
}

// Getter for blocked status
bool Customer::getIsBlocked() const
{
    return this->isBlocked;
}
// Setter for blocking status
void Customer::setBlocked(bool status)
{
    this->isBlocked = status;
}

// Getter for session count
int Customer::getSessionCount() const
{
    return this->sessionCount;
}

// Increment session count after a successful filter application
void Customer::incrementSessionCount()
{
    this->sessionCount++;
}

// Helper function: Prepares the customer data to be written as a single line in a text file
string Customer::toFileString() const
{
    string blockStatus = "0";
    if (this->isBlocked)
    {
        blockStatus = "1";
    }

    return this->cnic + "|" + this->password + "|" + this->fullName + "|" + this->gender + "|" + this->phone + "|" + this->city + "|" + blockStatus + "|" + to_string(this->sessionCount);
}
