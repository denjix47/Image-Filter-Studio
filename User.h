#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User {
protected:
    string cnic;
    string password;
    string fullName;

public:
    User(string cnic, string password, string fullName);
    virtual ~User();

    // Pure virtual function
    virtual void showMenu() = 0;

    virtual bool login(string inputCnic, string inputPwd);
    virtual void logout();

    // Getters
    string getCnic() const;
    string getFullName() const;
};

#endif 