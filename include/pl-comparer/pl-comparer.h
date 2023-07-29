#ifndef PLCOMPARER // include guard
#define PLCOMPARER

#include <string>

#include <curl/curl.h>
#include <nlohmann/json.hpp>

namespace PackageListComparer
{
  int compare(std::string arch);
  nlohmann::json loadJson(std::string first, std::string second);

  class Comparator
  {
  public:
    Comparator();
    Comparator(std::string first, std::string second);

    nlohmann::json getThisJson();

  private:
    int m_id;
    std::string m_name;
    nlohmann::json endresult;
  };
} // namespace PackageListComparer

#endif