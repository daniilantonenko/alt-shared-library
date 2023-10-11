#include <fstream>
#include <iostream>
#include <PLcomparer/PLcomparer.h>

using namespace std;
using namespace PackageListComparer;

using json = nlohmann::json;

// Save received data to file
void saveJsonToFile(const json &data, const string name)
{
    try
    {
        ofstream file;
        string filename = name + ".json";
        file.open(filename);

        if (file.is_open())
        {
            file << data.dump(4) << endl;
        }
        
        file.close();

        cout << "File \"" << filename << "\" was saved successfully.\n";
    }
    catch (const char *str)
    {
        cerr << "Caught exception:\n";
    }
}

int main()
{
    string arch = "x86_64";

    string first = "p10";
    string second = "sisyphus";

    json firstJ = loadJson(first, arch);
    json secondJ = loadJson(second, arch);

    json resultJson = comparing(firstJ, secondJ);

    saveJsonToFile(resultJson, "resultJson");

    return 0;
}
