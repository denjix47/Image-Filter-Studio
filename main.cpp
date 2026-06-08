#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <fstream>
#include <ctime>
#include "CustomerManager.h"
#include "CatalogManager.h"
#include "SessionManager.h"
#include "Admin.h"
#include "Customer.h"
#include "Image.h"
#include "FilterSession.h"
#include "Grayscale.h"
#include "Invert.h"
#include "BrightnessAdjust.h"
#include "ContrastStretch.h"
#include "RedChannelOnly.h"
#include "GreenChannelOnly.h"
#include "BlueChannelOnly.h"
#include "BoxBlur.h"
#include "FlipHorizontal.h"
#include "FlipVertical.h"
using namespace std;

// ANSI Color Codes
const string RESET = "\033[0m";
const string CYAN = "\033[36m";
const string GREEN = "\033[32m";
const string RED = "\033[31m";
const string YELLOW = "\033[33m";

int main()
{
    // 1. Initialize our File Managers and load existing data
    CustomerManager custManager;
    CatalogManager catManager;
    SessionManager sessManager;

    custManager.load();
    catManager.load();

    int mainChoice = 0;
    int failedLoginAttempts = 0; // Tracks failed logins for the 3-attempt lockout

    // The Main Startup Screen Loop
    while (mainChoice != 4)
    {
        cout << CYAN << "\n=== IMAGE FILTER STUDIO ===\n"
             << RESET;
        cout << "1. Admin Login\n";
        cout << "2. Customer Login\n";
        cout << "3. New Customer? Register here\n";
        cout << RED << "4. Exit\n"
             << RESET;
        cout << YELLOW << "Your choice: " << RESET;
        cin >> mainChoice;

        if (mainChoice == 1)
        {
            // === ADMIN LOGIN ===
            string cnic, pwd;
            cout << "Enter Admin CNIC: ";
            cin >> cnic;
            cout << "Enter Password: ";
            cin >> pwd;

            Admin adminUser;
            if (adminUser.login(cnic, pwd))
            {
                cout << GREEN << "\nLogin Successful!\n"
                     << RESET;

                int adminChoice = 0;
                while (adminChoice != 4)
                {
                    adminUser.showMenu();
                    cin >> adminChoice;

                    if (adminChoice == 1)
                        adminUser.manageCatalog(catManager); // Delegated to Admin.cpp
                    else if (adminChoice == 2)
                        adminUser.manageCustomers(custManager); // Delegated to Admin.cpp
                    else if (adminChoice == 3)
                        adminUser.viewAllSessions(sessManager); // Delegated to Admin.cpp
                    else if (adminChoice == 4)
                        adminUser.logout();
                }
            }
            else
            {
                cout << "Invalid Admin credentials.\n";
            }
        }
        else if (mainChoice == 2)
        {
            // === CUSTOMER LOGIN ===
            string cnic, pwd;
            cout << "Enter CNIC: ";
            cin >> cnic;
            cout << "Enter Password: ";
            cin >> pwd;

            Customer *foundUser = custManager.searchByCNIC(cnic);

            if (foundUser != nullptr && foundUser->login(cnic, pwd))
            {
                failedLoginAttempts = 0; // Reset attempts on successful login

                if (foundUser->getIsBlocked())
                {
                    cout << RED << "Your account has been blocked by an Administrator.\n"
                         << RESET;
                }
                else
                {
                    cout << GREEN << "\nLogin Successful!\n"
                         << RESET;

                    Image myImage;
                    FilterSession session(foundUser, &myImage);

                    string finalPipelineString = ""; // Declared outside menu loop to persist for saving

                    int custChoice = 0;
                    while (custChoice != 6)
                    {
                        foundUser->showMenu();
                        cin >> custChoice;

                        if (custChoice == 1)
                        {
                            cout << "\n--- Available Filters ---\n";
                            vector<FilterRecord> cat = catManager.getCatalog();
                            for (int i = 0; i < cat.size(); i++)
                            {
                                cout << cat[i].id << " | " << cat[i].name << " [" << cat[i].category << "] - "
                                     << (cat[i].enabled ? "Enabled" : "Disabled") << "\n";
                            }
                        }
                        else if (custChoice == 2)
                        {
                            string path;
                            cout << "Enter path to image file: ";
                            cin >> path;
                            cout << "Loading image file...\n";
                            if (myImage.loadFromFile(path))
                            {
                                cout << "Image loaded: " << myImage.getWidth() << " x " << myImage.getHeight() << " pixels\n";
                                myImage.displayASCII();
                                cout << "Image ready. Now build your filter pipeline.\n";
                            }
                        }
                        else if (custChoice == 3)
                        {
                            cout << "\n=== Build Filter Pipeline ===\n";
                            vector<string> currentPipelineNames;
                            int filterId;
                            cout << "Enter filter ID to add (0 to finish): ";

                            while (cin >> filterId && filterId != 0)
                            {
                                string idStr = (filterId < 10) ? "0" + to_string(filterId) : to_string(filterId);

                                if (catManager.isEnabled(idStr))
                                {
                                    string addedName = "";

                                    if (filterId == 1)
                                    {
                                        session.addFilter(new Grayscale());
                                        addedName = "Grayscale";
                                    }
                                    else if (filterId == 2)
                                    {
                                        session.addFilter(new Invert());
                                        addedName = "Invert";
                                    }
                                    else if (filterId == 3)
                                    {
                                        int amount;
                                        cout << "Enter brightness amount (-100 to +100): ";
                                        cin >> amount;
                                        session.addFilter(new BrightnessAdjust(amount));
                                        string sign = (amount > 0) ? "+" : "";
                                        addedName = "Brightness Adjust(" + sign + to_string(amount) + ")";
                                    }
                                    else if (filterId == 4)
                                    {
                                        session.addFilter(new ContrastStretch());
                                        addedName = "Contrast Stretch";
                                    }
                                    else if (filterId == 5)
                                    {
                                        session.addFilter(new RedChannelOnly());
                                        addedName = "Red Channel Only";
                                    }
                                    else if (filterId == 6)
                                    {
                                        session.addFilter(new GreenChannelOnly());
                                        addedName = "Green Channel Only";
                                    }
                                    else if (filterId == 7)
                                    {
                                        session.addFilter(new BlueChannelOnly());
                                        addedName = "Blue Channel Only";
                                    }
                                    else if (filterId == 8)
                                    {
                                        session.addFilter(new BoxBlur());
                                        addedName = "Box Blur (3x3)";
                                    }
                                    else if (filterId == 9)
                                    {
                                        session.addFilter(new FlipHorizontal());
                                        addedName = "Flip Horizontal";
                                    }
                                    else if (filterId == 10)
                                    {
                                        session.addFilter(new FlipVertical());
                                        addedName = "Flip Vertical";
                                    }

                                    currentPipelineNames.push_back(addedName);
                                    cout << "Added: " << addedName << "\n";
                                    cout << "Pipeline: [ ";
                                    for (int i = 0; i < currentPipelineNames.size(); i++)
                                    {
                                        cout << currentPipelineNames[i];
                                        if (i < currentPipelineNames.size() - 1)
                                            cout << " -> ";
                                    }
                                    cout << " ]\n";
                                }
                                else
                                {
                                    cout << RED << "Error: Filter is disabled by Admin or invalid.\n"
                                         << RESET;
                                }
                                cout << "Enter filter ID to add (0 to finish): ";
                            }
                            cout << "Pipeline finalised. " << currentPipelineNames.size() << " filters ready to apply.\n";

                            // Format and save the final string for the SessionManager
                            finalPipelineString = "[ ";
                            for (int i = 0; i < currentPipelineNames.size(); i++)
                            {
                                finalPipelineString += currentPipelineNames[i];
                                if (i < currentPipelineNames.size() - 1)
                                    finalPipelineString += " -> ";
                            }
                            finalPipelineString += " ]";
                        }
                        else if (custChoice == 4)
                        {
                            session.applyAll(myImage);

                            char saveChoice;
                            cout << "Save result? (y/n): ";
                            cin >> saveChoice;
                            if (saveChoice == 'y' || saveChoice == 'Y')
                            {
                                // Auto-generate filename: CNIC_YYYYMMDD_HHMMSS.png
                                time_t now = time(0);
                                tm *ltm = localtime(&now);
                                char timestamp[32];
                                snprintf(timestamp, sizeof(timestamp), "%04d%02d%02d_%02d%02d%02d",
                                         1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday,
                                         ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
                                string autoFilename = foundUser->getCnic() + "_" + timestamp + ".png";

                                session.saveResult(autoFilename);
                                cout << "Image saved as: " << autoFilename << "\n";

                                // Log the session with all 4 fields
                                sessManager.logSession(foundUser->getCnic(), finalPipelineString, autoFilename);

                                // Increment session count and persist to customers.txt
                                foundUser->incrementSessionCount();
                                custManager.save();
                            }
                            session.clearPipeline();
                            finalPipelineString = "";
                        }
                        else if (custChoice == 5)
                        {
                            sessManager.displayCustomerHistory(foundUser->getCnic());
                        }
                        else if (custChoice == 6)
                        {
                            foundUser->logout();
                        }
                    }
                }
            }
            else
            {
                failedLoginAttempts++;
                cout << RED << "Invalid CNIC or Password. Attempts: " << RESET << failedLoginAttempts << "/3\n";
                if (failedLoginAttempts >= 3)
                {
                    cout << RED << "SYSTEM LOCKED. Too many failed attempts. Security protocol engaged.\n"
                         << RESET;
                    return 0;
                }
            }
        }
        else if (mainChoice == 3)
        {
            // === REGISTRATION ===
            string cnic, pwd, name, gender, phone, city;
            cout << "\n--- Account Registration ---\n";
            cout << "Enter CNIC (exactly 13 digits): ";
            cin >> cnic;

            // Validation 1: CNIC Length Check
            if (cnic.length() != 13)
            {
                cout << RED << "Error: CNIC must be exactly 13 characters.\n"
                     << RESET;
                continue;
            }

            // Validation 2: Check if CNIC was permanently blocked by Admin
            bool isPermanentlyBlocked = false;
            ifstream blockFile("blocked_cnics.txt");
            string bLine;
            while (getline(blockFile, bLine))
            {
                if (bLine == cnic)
                {
                    isPermanentlyBlocked = true;
                    break;
                }
            }
            blockFile.close();

            if (isPermanentlyBlocked)
            {
                cout << RED << "Error: This CNIC has been permanently blocked by an Administrator.\n"
                     << RESET;
                continue;
            }

            // Validation 3: Check if already registered
            if (custManager.searchByCNIC(cnic) != nullptr)
            {
                cout << RED << "Error: This CNIC is already registered.\n"
                     << RESET;
                continue;
            }

            cout << "Enter Password (Min 9 chars, 1 uppercase, 1 digit): ";
            cin >> pwd;

            // Validation 4: Password complexity
            bool hasUpper = false, hasDigit = false;
            for (char c : pwd)
            {
                if (isupper(c))
                    hasUpper = true;
                if (isdigit(c))
                    hasDigit = true;
            }
            if (pwd.length() < 9 || !hasUpper || !hasDigit)
            {
                cout << RED << "Error: Password must be at least 9 chars, with 1 uppercase and 1 number.\n"
                     << RESET;
                continue;
            }

            cout << "Enter Full Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Gender (M/F/Other): ";
            cin >> gender;
            cout << "Enter Phone: ";
            cin >> phone;
            cout << "Enter City: ";
            cin >> city;

            Customer newUser(cnic, pwd, name, gender, phone, city, false, 0);
            custManager.addCustomer(newUser);
            cout << "Registration successful! You can now log in.\n";
        }
    }

    cout << CYAN << "Exiting Image Filter Studio. Goodbye!\n"
         << RESET;
    return 0;
}