#include "CatalogManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Constructor initializes the filename for catalog data
CatalogManager::CatalogManager()
{
    this->FILENAME = "catalog.txt";
}

// Loads the catalog from the text file into the in-memory vector
void CatalogManager::load()
{
    this->catalog.clear();
    ifstream file(this->FILENAME);

    if (!file.is_open())
    {
        cout << "Warning: " << this->FILENAME << " not found. Please create it.\n";
        return;
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        FilterRecord record;
        string enabledStr;

        // Split by the | character
        getline(ss, record.id, '|');
        getline(ss, record.name, '|');
        getline(ss, record.category, '|');
        getline(ss, enabledStr, '|');

        record.enabled = (enabledStr == "1");
        this->catalog.push_back(record);
    }
    file.close();
}

// Saves the current state of the catalog vector back to the text file
void CatalogManager::save()
{
    ofstream file(this->FILENAME);
    if (file.is_open())
    {
        for (int i = 0; i < this->catalog.size(); i++)
        {
            file << this->catalog[i].id << "|"
                 << this->catalog[i].name << "|"
                 << this->catalog[i].category << "|"
                 << (this->catalog[i].enabled ? "1" : "0") << "\n";
        }
        file.close();
    }
}

// Toggles the enabled status of a filter by its ID and saves the updated catalog
void CatalogManager::toggle(string id)
{
    for (int i = 0; i < this->catalog.size(); i++)
    {
        if (this->catalog[i].id == id)
        {
            this->catalog[i].enabled = !this->catalog[i].enabled;
            save();

            cout << "Filter " << this->catalog[i].name << " is now " << (this->catalog[i].enabled ? "Enabled" : "Disabled") << ".\n";
            return;
        }
    }
    cout << "Error: Filter ID not found.\n";
}

// Checks if a specific filter is allowed to be used
bool CatalogManager::isEnabled(string id)
{
    for (int i = 0; i < this->catalog.size(); i++)
    {
        if (this->catalog[i].id == id)
        {
            return this->catalog[i].enabled;
        }
    }
    return false;
}

// Getter for the menu display
vector<FilterRecord> CatalogManager::getCatalog() const
{
    return this->catalog;
}