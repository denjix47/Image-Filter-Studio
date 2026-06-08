#include "User.h"
#include <iostream>

// Parameterized constructor
User::User(string cnic, string password, string fullName)
{
    this->cnic = cnic;
    this->password = password;
    this->fullName = fullName;
    cout << "[System] User base created.\n";
}

// Virtual destructor
User::~User() { cout << "[System] User base destroyed.\n"; }

// Base login logic
bool User::login(string inputCnic, string inputPwd)
{
    if (this->cnic == inputCnic && this->password == inputPwd)
    {
        return true;
    }
    return false;
}

void User::logout()
{
    cout << this->fullName << " has logged out successfully.\n";
}

// Getters
string User::getCnic() const { return this->cnic; }
string User::getFullName() const { return this->fullName; }