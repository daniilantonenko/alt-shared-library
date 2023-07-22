#ifndef PLCOMPARER // include guard
#define PLCOMPARER

#include <iostream>
#include <string>

#include <curl/curl.h>
#include <nlohmann/json.hpp>

namespace PackageListComparer {
int compare(std::string arch);

class Comparator {
public:
  Comparator();
  Comparator(int id, std::string const &name);
  Comparator(nlohmann::json data);
  Comparator(nlohmann::json first, nlohmann::json second);

  nlohmann::json getJson();
  nlohmann::json compare(nlohmann::json first , nlohmann::json second);
  nlohmann::json getThisJson();

private:
  int m_id;
  std::string m_name;
  nlohmann::json endresult;
};
} // namespace PackageListComparer

#endif