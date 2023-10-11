#include <iostream>
#include <PLcomparer/PLcomparer.h>

using namespace std;
using namespace PackageListComparer;

using json = nlohmann::json;

int main()
{
    string arch = "x86_64";

    string first = "p10";
    string second = "sisyphus";

    json firstJ = loadJson(first, arch);
    json secondJ = loadJson(second, arch);

    json resultJson = comparing(firstJ, secondJ);

    cout << resultJson.dump(4) << "\n";

    return 0;
}
