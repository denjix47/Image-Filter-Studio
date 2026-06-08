#include "SessionManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <ctime>

// Constructor initializes the filename for session data
SessionManager::SessionManager()
{
    this->FILENAME = "sessions.txt";
}

// Appends a new session to the text file
// Format: CNIC|Timestamp|FiltersApplied|OutputFile
void SessionManager::logSession(string cnic, string pipelineDetails, string outputFile)
{
    ofstream file(this->FILENAME, ios::app);

    if (file.is_open())
    {
        // Grab the current system time
        time_t now = time(0);
        tm *ltm = localtime(&now);

        char timestamp[32];
        snprintf(timestamp, sizeof(timestamp), "%04d%02d%02d_%02d%02d%02d",
                 1900 + ltm->tm_year,
                 1 + ltm->tm_mon,
                 ltm->tm_mday,
                 ltm->tm_hour,
                 ltm->tm_min,
                 ltm->tm_sec);

        // Write all 4 fields separated by pipes
        file << cnic << "|" << timestamp << "|" << pipelineDetails << "|" << outputFile << "\n";
        file.close();
    }
}

// Searches the file and prints only the rows matching the logged-in CNIC
void SessionManager::displayCustomerHistory(string cnic)
{
    ifstream file(this->FILENAME);
    if (!file.is_open())
    {
        cout << "No session history found.\n";
        return;
    }

    cout << "\n=== Your Session History ===\n";
    string line;
    bool foundAny = false;

    while (getline(file, line))
    {
        stringstream ss(line);
        string fileCnic, timestamp, details, outputFile;

        getline(ss, fileCnic, '|');
        getline(ss, timestamp, '|');
        getline(ss, details, '|');
        getline(ss, outputFile, '|');

        if (fileCnic == cnic)
        {
            cout << "[" << timestamp << "] Applied: " << details << " | Saved as: " << outputFile << "\n";
            foundAny = true;
        }
    }

    if (!foundAny)
    {
        cout << "You have no recorded sessions yet.\n";
    }
    file.close();
}

// Prints everything in the file for the Admin
void SessionManager::displayAllSessions()
{
    ifstream file(this->FILENAME);
    if (!file.is_open())
    {
        cout << "No session history found.\n";
        return;
    }

    cout << "\n=== All System Sessions ===\n";
    string line;

    while (getline(file, line))
    {
        stringstream ss(line);
        string fileCnic, timestamp, details, outputFile;

        getline(ss, fileCnic, '|');
        getline(ss, timestamp, '|');
        getline(ss, details, '|');
        getline(ss, outputFile, '|');

        cout << "CNIC: " << fileCnic << " | Date: " << timestamp << " | Pipeline: " << details << " | File: " << outputFile << "\n";
    }
    file.close();
}