#ifndef CATALOGMANAGER_H
#define CATALOGMANAGER_H

#include <string>
#include <vector>
using namespace std;

struct FilterRecord
{
    string id;
    string name;
    string category;
    bool enabled;
};

class CatalogManager
{
private:
    string FILENAME;
    vector<FilterRecord> catalog;

public:
    CatalogManager();

    // Core File I/O
    void load();
    void save();

    // Admin toggle and status check
    void toggle(string id);
    bool isEnabled(string id);

    // Helper to get the whole catalog for the Customer menu
    vector<FilterRecord> getCatalog() const;
};

#endif