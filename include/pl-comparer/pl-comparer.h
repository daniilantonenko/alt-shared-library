#ifndef PLCOMPARER // include guard
#define PLCOMPARER

#include <string>

#include <curl/curl.h>
#include <nlohmann/json.hpp>

// namespace PackageListComparer 
namespace PackageListComparer
{
  nlohmann::json loadJson(std::string arch);

  nlohmann::json simpler(const nlohmann::json &source);

  nlohmann::json comparing(const nlohmann::json &source, const nlohmann::json &target);

  class Comparator
  {
  public:
    Comparator();
    Comparator(std::string first, std::string second);

    void simpler();
    nlohmann::json getThisJson();

  private:
    //int m_id;
    //std::string m_name;
    nlohmann::json patch;
  };
} 

#endif