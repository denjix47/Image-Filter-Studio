#include "CustomerManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
using namespace std;

// Constructor initializes the filename for customer data
CustomerManager::CustomerManager()
{
    this->FILENAME = "customers.txt";
}

void CustomerManager::load()
{
    this->customerList.clear();

    try
    {
        ifstream file(this->FILENAME);
        if (!file.is_open())
        {
            throw runtime_error("File not found or could not be opened.");
        }

        string line;
        // Read line by line
        while (getline(file, line))
        {
            stringstream ss(line);
            string cnic, pwd, name, gender, phone, city, blockedStr, sessionCountStr;

            // Extract each piece of data separated by the | character
            getline(ss, cnic, '|');
            getline(ss, pwd, '|');
            getline(ss, name, '|');
            getline(ss, gender, '|');
            getline(ss, phone, '|');
            getline(ss, city, '|');
            getline(ss, blockedStr, '|');
            getline(ss, sessionCountStr, '|');

            bool isBlocked = (blockedStr == "1");
            int sessionCount = sessionCountStr.empty() ? 0 : stoi(sessionCountStr);

            // Create the customer object and add it to our in-memory vector
            Customer tempCust(cnic, pwd, name, gender, phone, city, isBlocked, sessionCount);
            this->customerList.push_back(tempCust);
        }
        file.close();
    }
    catch (const exception &e)
    {
        // It is perfectly normal for the file not to exist on the very first run
        // We catch the exception silently (or you can print a tiny warning) to prevent crashing
    }
}

// Rewrites the entire vector back to the text file
void CustomerManager::save()
{
    ofstream file(this->FILENAME);
    if (file.is_open())
    {
        for (int i = 0; i < this->customerList.size(); i++)
        {
            // We use the helper function we wrote in Customer.cpp earlier!
            file << this->customerList[i].toFileString() << "\n";
        }
        file.close();
    }
}

// Search utility
Customer *CustomerManager::searchByCNIC(string cnic)
{
    for (int i = 0; i < this->customerList.size(); i++)
    {
        if (this->customerList[i].getCnic() == cnic)
        {
            return &this->customerList[i];
        }
    }
    return nullptr;
}

// Search utility for the Admin panel
Customer *CustomerManager::searchByName(string name)
{
    for (int i = 0; i < this->customerList.size(); i++)
    {
        if (this->customerList[i].getFullName() == name)
        {
            return &this->customerList[i];
        }
    }
    return nullptr;
}

// Updates the block status and saves the file
void CustomerManager::block(string cnic)
{
    Customer *c = searchByCNIC(cnic);
    if (c != nullptr)
    {
        c->setBlocked(true);
        save();

        ofstream blockFile("blocked_cnics.txt", ios::app);
        if (blockFile.is_open())
        {
            blockFile << cnic << "\n";
            blockFile.close();
        }

        cout << "Customer " << cnic << " has been blocked.\n";
    }
    else
    {
        cout << "Customer not found.\n";
    }
}

// Checks if a CNIC is blocked (used during login)
bool CustomerManager::isBlockedCNIC(string cnic)
{
    Customer *c = searchByCNIC(cnic);
    if (c != nullptr)
    {
        return c->getIsBlocked();
    }
    return false;
}

// Deletes a customer by CNIC and saves the updated list
void CustomerManager::deleteCustomer(string cnic)
{
    for (auto it = this->customerList.begin(); it != this->customerList.end(); ++it)
    {
        if (it->getCnic() == cnic)
        {
            this->customerList.erase(it);
            save();
            cout << "Customer " << cnic << " deleted successfully.\n";
            return;
        }
    }
    cout << "Customer not found.\n";
}

void CustomerManager::addCustomer(const Customer &c)
{
    this->customerList.push_back(c);
    save();
}