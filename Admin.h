#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include "CatalogManager.h"
#include "CustomerManager.h"
#include "SessionManager.h"
using namespace std;

class Admin : public User
{
private:
    const string ADMIN_CNIC = "admin";
    const string ADMIN_PWD = "admin";

public:
    Admin();
    ~Admin();

    void showMenu() override;
    bool login(string inputCnic, string inputPwd) override;

    // Admin specific functions
    void manageCatalog(CatalogManager &catManager);
    void manageCustomers(CustomerManager &custManager);
    void viewAllSessions(SessionManager &sessManager);

    void blockCustomer(CustomerManager &custManager);
    void deleteCustomer(CustomerManager &custManager);
    void toggleFilter(CatalogManager &catManager);
};

#endif 