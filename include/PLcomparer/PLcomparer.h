#ifndef PLCOMPARER // include guard
#define PLCOMPARER

#include <string>
#include <iostream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

// namespace PackageListComparer 
namespace PackageListComparer
{
  nlohmann::json loadJson(const std::string branch, const std::string arch);
  nlohmann::json comparing(const nlohmann::json &source, const nlohmann::json &target);
} 

#endif