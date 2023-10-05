#ifndef PLCOMPARER // include guard
#define PLCOMPARER

#include <string>
#include <iostream>
#include <vector>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

// namespace PackageListComparer 
namespace PackageListComparer
{
  int CompareVersions(std::string version1, std::string version2);
  nlohmann::json loadJson(const std::string branch, const std::string arch);
  nlohmann::json comparing(const nlohmann::json &source, const nlohmann::json &target);
} 

#endif