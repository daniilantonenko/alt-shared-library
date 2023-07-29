#include <fstream>
#include <iostream>
#include <pl-comparer/pl-comparer.h>

using plc = PackageListComparer::Comparator;
using json = nlohmann::json;

int main()
{
	std::cout << "Start new comprare:" << std::endl;

	std::string first = "x86_64";
	std::string second = "ppc64le";

	plc newComprare(first, second);
	json resultJson = newComprare.getThisJson();

	std::ofstream myfile;
	myfile.open("result.json");
	myfile << resultJson.dump(4);
	myfile.close();

	std::cout << "End." << std::endl;

	return 0;
}
