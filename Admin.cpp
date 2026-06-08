#include "Admin.h"
#include <iostream>

// Parameterized constructor
Admin::Admin() : User("admin", "admin", "System Administrator")
{
    cout << "[System] Admin derived created.\n";
}

// Destructor
Admin::~Admin()
{
    cout << "[System] Admin derived destroyed.\n";
}

// Admin login overrides base login with hardcoded credentials
bool Admin::login(string inputCnic, string inputPwd)
{
    if (inputCnic == this->ADMIN_CNIC && inputPwd == this->ADMIN_PWD)
    {
        return true;
    }
    return false;
}

// Admin menu
void Admin::showMenu()
{
    cout << "\n=== ADMIN PANEL Image Filter Studio ===\n";
    cout << "1. Manage Filter Catalog\n";
    cout << "2. Manage Customers\n";
    cout << "3. View All Sessions\n";
    cout << "4. Logout\n";
    cout << "Your choice: ";
}

// ==========================================
// ADMIN IMPLEMENTATIONS
// ==========================================

// Admin function to manage the filter catalog
void Admin::manageCatalog(CatalogManager &catManager)
{
    int catChoice = 0;
    while (catChoice != 2)
    {
        cout << "\n--- Catalog Management ---\n";
        vector<FilterRecord> cat = catManager.getCatalog();

        // Display the current status of all filters
        for (int i = 0; i < cat.size(); i++)
        {
            cout << cat[i].id << " | " << cat[i].name << " - " << (cat[i].enabled ? "Enabled" : "Disabled") << "\n";
        }
        cout << "\n1. Toggle Filter Status\n";
        cout << "2. Go Back\n";

        cout << "Choice: ";
        cin >> catChoice;

        if (catChoice == 1)
        {
            toggleFilter(catManager);
        }
    }
}

// Admin function to toggle filter status by ID
void Admin::toggleFilter(CatalogManager &catManager)
{
    string toggleId;
    cout << "Enter Filter ID to toggle (e.g., 01): ";
    cin >> toggleId;
    catManager.toggle(toggleId);
}

// Admin function to manage customers (block/delete)
void Admin::manageCustomers(CustomerManager &custManager)
{
    int custMenuChoice = 0;
    while (custMenuChoice != 3)
    {
        cout << "\n--- Customer Management ---\n";
        cout << "1. Block a Customer\n";
        cout << "2. Delete a Customer\n";
        cout << "3. Go Back\n";
        cout << "Choice: ";
        cin >> custMenuChoice;

        if (custMenuChoice == 1)
        {
            blockCustomer(custManager);
        }
        else if (custMenuChoice == 2)
        {
            deleteCustomer(custManager);
        }
    }
}

// Admin function to block a customer by CNIC
void Admin::blockCustomer(CustomerManager &custManager)
{
    string bCnic;
    cout << "Enter CNIC to block: ";
    cin >> bCnic;
    custManager.block(bCnic); // The manager handles saving to customers.txt
}

// Admin function to delete a customer by CNIC
void Admin::deleteCustomer(CustomerManager &custManager)
{
    string dCnic;
    cout << "Enter CNIC to delete: ";
    cin >> dCnic;
    custManager.deleteCustomer(dCnic);
}

// Admin function to view all sessions in the system
void Admin::viewAllSessions(SessionManager &sessManager)
{
    sessManager.displayAllSessions();
}