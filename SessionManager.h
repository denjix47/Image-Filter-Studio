#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include <string>
#include <vector>
using namespace std;

class SessionManager
{
private:
    string FILENAME;

public:
    SessionManager();

    // Writes a new completed pipeline to the text file
    void logSession(string cnic, string pipelineDetails, string outputFile);

    // Reads history for a specific customer
    void displayCustomerHistory(string cnic);

    // Reads all history for the Admin panel
    void displayAllSessions();
};

#endif