#include <fstream>
#include <iostream>
#include <pl-comparer/pl-comparer.h>

using namespace std;

using plc = PackageListComparer::Comparator;
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

    string first = "noarch";
    string second = "x86_64";
    // Get all arch by branch: https://rdb.altlinux.org/api/site/all_pkgset_archs?branch=p10
    // x86_64, ppc64le, i586, armh, aarch64, noarch

    json firstJ = PackageListComparer::loadJson("aarch64");
    // saveJsonToFile(firstJ, "aarch64");
    json secondJ = PackageListComparer::loadJson("x86_64");
    // saveJsonToFile(secondJ, "x86_64");

    json resultJson = PackageListComparer::comparing(firstJ, secondJ);

    /*cout << "resultJson:\n"
         << resultJson.dump(4) << "\n";*/
    saveJsonToFile(resultJson, "resultJson");

    /*plc newComprare(first, second);
    json resultJsonComp = newComprare.getThisJson();
    saveJsonToFile(resultJsonComp, "resultJsonComp");*/
    /*
        json simpleresultJson = PackageListComparer::simpler(resultJson);
        cout << "simpleresultJson:\n"
             << simpleresultJson.dump(4) << "\n";
    */
    // saveJsonToFile(resultJson, "result");

    cout << "End.\n";

    return 0;
}
