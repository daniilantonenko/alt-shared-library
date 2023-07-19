#include <pl-comparer/pl-comparer.h>
using namespace PackageListXComparer;

int main(int, char*[])
{
    auto result = PackageListXComparer::compare(5);
    //std::string result = "Some result";
    std::cout << result << "\n";
    return 0;
}