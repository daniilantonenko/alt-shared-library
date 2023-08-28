# Package list comprare
Shared library for comparing binary packages of 2 branches. 

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
Using public REST API for database ALT Linux:
```cpp
std::string first = "aarch64";
std::string second = "x86_64";
json source = loadJson(first);
json target = loadJson(second);
```
### Run comparison
Using public REST API for database ALT Linux:
```cpp
nlohmann::json resultJson = comparing(first, second);
```


## Plan
- [X] Basic comparison functionality
- [X] Get lists of binary packages
- [ ] CLI utility
- [ ] Installation by FHS standard