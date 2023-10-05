#include <CLI/CLI.hpp>
#include <fstream>

#include <PLcomparer/PLcomparer.h>

using namespace PackageListComparer;

using json = nlohmann::json;

void saveJsonToFile(const json &data, const std::string name);

int main(int argc, char **argv)
{

    CLI::App app{"PLcomparer \nExample branches: sisyphus и p10 \n"};

    // Flags - Actions with results
    bool print_flag{false};
    app.add_flag("-p,--print", print_flag, "Print Json comparison result")->group("Result");

    bool dump_flag{false};
    app.add_flag("-d,--dump", dump_flag, "Print beautiful Json dump comparison result")->group("Result");

    bool save_flag{false};
    app.add_flag("-f,--file", save_flag, "Saving beautiful Json dump comparison result")->group("Result");

    std::string sourceBranch;
    app.add_option("-s,--source", sourceBranch, "Branch source name")->required();

    std::string targetBranch;
    app.add_option("-t,--target", targetBranch, "Branch target name")->required();

    std::string arch;
    app.add_option("-a,--arch", arch, "Arch name")->required();


    CLI11_PARSE(app, argc, argv);

    if (app.count("-s") && app.count("-t"))
    {
        // TODO: input data for availability
        std::string first = sourceBranch;
        std::string second = targetBranch;

        json firstJ = loadJson(first, arch);
        json secondJ = loadJson(second, arch);

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
            std::cout << "Summary:\n"
                      << "Arch: " << arch << "\n"
                      << "Source branch: " << sourceBranch << "\n"
                      << "Target branch: " << targetBranch << "\n"
                      << "Comparison size: " << (int) resultJson.size() << "\n"
                      << "Comparison sizeof: " << (int) sizeof(resultJson) << "\n";
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