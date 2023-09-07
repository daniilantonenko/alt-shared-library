#include <CLI/CLI.hpp>
#include <iostream>
#include <string>

#include <PLcomparer/PLcomparer.h>

using namespace PackageListComparer;

using json = nlohmann::json;

int main(int argc, char **argv)
{
    // CLI::App app;
    CLI::App app{"PLcomparer \nExample branches: x86_64, ppc64le, i586, armh, aarch64, noarch \n"};
    std::string sourceBranch;
    app.add_option("-s,--source", sourceBranch, "Branch source name");

    std::string targetBranch;
    app.add_option("-t,--target", targetBranch, "Branch target name");

    CLI11_PARSE(app, argc, argv);

    //std::cout << "Source: " << sourceBranch << ", direct count: " << app.count("-s") << std::endl;
    //<< ", opt count: " << opt->count() << std::endl;

    //std::cout << "Target: " << targetBranch << ", direct count: " << app.count("-t") << std::endl;
    //<< ", opt count: " << opt->count() << std::endl;

    if (app.count("-s") && app.count("-t"))
    {
        std::cout << "BINGO" << std::endl;
        /*std::string first = "aarch64";
        std::string second = "x86_64";

        json firstJ = loadJson(sourceBranch);
        json secondJ = loadJson(targetBranch);

        json resultJson = comparing(firstJ, secondJ);

        std::cout << "resultJson:\n"
                  << resultJson.dump(4) << "\n";*/
    }

    return 0;
}