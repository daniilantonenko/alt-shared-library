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
    string first = "aarch64";
    string second = "x86_64";
    // Get all arch by branch: https://rdb.altlinux.org/api/site/all_pkgset_archs?branch=p10
    // x86_64, ppc64le, i586, armh, aarch64, noarch

    json firstJ = loadJson(first);
    json secondJ = loadJson(second);

    json resultJson = comparing(firstJ, secondJ);

    saveJsonToFile(resultJson, "resultJson");

    return 0;
}
