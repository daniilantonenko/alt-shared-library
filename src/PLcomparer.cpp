#include <CLI/CLI.hpp>
#include <fstream>
#include <iostream>
#include <string>

#include <PLcomparer/PLcomparer.h>

using namespace PackageListComparer;

using json = nlohmann::json;

void saveJsonToFile(const json &data, const std::string name);

int main(int argc, char **argv)
{

    CLI::App app{"PLcomparer \nExample architectures: x86_64, ppc64le, i586, armh, aarch64, noarch \n"};

    // Flags - Actions with results
    bool print_flag{false};
    app.add_flag("-p,--print", print_flag, "Print Json comparison result")->group("Result");

    bool dump_flag{false};
    app.add_flag("-d,--dump", dump_flag, "Print beautiful Json dump comparison result")->group("Result");

    bool save_flag{false};
    app.add_flag("-f,--file", save_flag, "Saving beautiful Json dump comparison result")->group("Result");

    std::string branch;
    app.add_option("-b,--branch", branch, "Branch name")->required();

    std::string sourceArch;
    app.add_option("-s,--source", sourceArch, "Arch source name")->required();

    std::string targetArch;
    app.add_option("-t,--target", targetArch, "Arch target name")->required();

    std::string actionСomparison = "default";
    app.add_option("-c,--comp", actionСomparison, "Сomparison action");

    CLI11_PARSE(app, argc, argv);

    if (app.count("-s") && app.count("-t"))
    {
        // TODO: Check architecture Arch input data for availability
        std::string first = sourceArch;
        std::string second = targetArch;

        json firstJ = loadJson(first);
        json secondJ = loadJson(second);

        json resultJson = comparing(firstJ, secondJ);

        if (print_flag)
        { 
            std::cout << resultJson << std::endl;
        }
        else if (dump_flag)
        {
            std::cout << resultJson.dump(4) << "\n";
        }
        else if (save_flag)
        {
            saveJsonToFile(resultJson, "resultJson");
        }
        else
        {
            // TODO: summary result
            std::cout << "Summary:\nsize: "
                      << (int) resultJson.size() << "\n";
        }
    }

    return 0;
}

// Save received data to file
void saveJsonToFile(const json &data, const std::string name)
{
    try
    {
        std::ofstream file;
        std::string filename = name + ".json";
        file.open(filename);
        file << data.dump(4);
        file.close();

        std::cout << "File \"" << filename << "\" was saved successfully.\n";
    }
    catch (const char *str)
    {
        std::cerr << "Caught exception:\n";
    }
}