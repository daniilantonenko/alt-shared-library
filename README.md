# Package list comprare
Shared library for comparing binary packages of 2 branches. 
Works only with json sorted in descending order!

Output JSON structure:
- **missing** (all packages that are in the 1st but not in the 2nd)
- **extra** (all packages that are in the 2nd but are not in the 1st)
- **updated** (all packages whose version-release is greater in the 1st than in the 2nd)

## Examples
Some examples to give you an idea how to use the class. Beside the examples below, you may want to browse the standalone example files. 

Has a dependency on [nlohmann::json](https://github.com/nlohmann/json).

### Add to project
```cpp
#include <pl-comparer/pl-comparer.h>
using namespace PackageListComparer;
using json = nlohmann::json;
```

### Getting binary packages
Specify architecture for comparison (ALT Linux p10). For example: X86_64, ppc64le, i586, armh, aarch64, noarch.
```cpp
std::string first = "aarch64";
std::string second = "x86_64";
json source = loadJson(first);
json target = loadJson(second);
```
### Run comparison
Make comparison and get result:
```cpp
nlohmann::json resultJson = comparing(first, second);
```


## Plan
- [X] Basic comparison functionality
- [X] Get lists of binary packages
- [ ] CLI utility
- [ ] Installation by FHS standard
- [ ] Getting arch by API
- [ ] Selecting a branch