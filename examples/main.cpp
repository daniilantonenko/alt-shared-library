#include <fstream>
#include <iostream>
#include <pl-comparer/pl-comparer.h>

using namespace std;
using namespace PackageListComparer;

using json = nlohmann::json;

// Save received data to file
void saveJsonToFile(const json &data, const string name)
{
    try
    {
        ofstream file;
        file.open(name + ".json");
        file << data.dump(4);
        file.close();
    }
    catch (const char *str)
    {
        cerr << "Caught exception:\n";
    }
}

int main()
{
    cout << "Start new comprare:\n";

    string first = "aarch64";
    string second = "x86_64";
    // Get all arch by branch: https://rdb.altlinux.org/api/site/all_pkgset_archs?branch=p10
    // x86_64, ppc64le, i586, armh, aarch64, noarch

    json firstJ = loadJson(first);
    json secondJ = loadJson(second);

    json resultJson = comparing(firstJ, secondJ);

    cout << "resultJson:\n"
         << resultJson.dump(4) << "\n";
    saveJsonToFile(resultJson, "resultJson");

    cout << "End.\n";

    return 0;
}
