#include <PLcomparer/PLcomparer.h>

namespace PackageListComparer
{

	static size_t WriteCallback(void *contents, size_t size, size_t nmemb,
								void *userp)
	{
		((std::string *)userp)->append((char *)contents, size * nmemb);
		return size * nmemb;
	}

	size_t findSplitter(const std::string s, int start = 0)
	{
		char prev, curr;

		for (int i = start; i < s.length(); i++)
		{
			curr = s[i];
			if ((isalpha(prev) && isdigit(curr)) || (isdigit(prev) && isalpha(curr)))
			{
				// Number has changed to a letter or vice versa
				return i;
			}
			else if (isalnum(curr) && ispunct(prev))
			{
				// Number or letter has changed to a separator
				return i - 1;
			}
			prev = s[i];
		}

		return -1;
	}

	std::vector<std::string> splitVersion(const std::string &version)
	{
		std::vector<std::string> result;
		size_t start = 0;
		size_t end = findSplitter(version);
		std::string substring;

		while (end != std::string::npos)
		{

			substring = version.substr(start, end - start);
			result.push_back(substring);

			// Bypassing the delimiter
			start = (ispunct(version[end])) ? end + 1 : end;

			end = findSplitter(version, start);
		}

		substring = version.substr(start);
		result.push_back(substring);

		return result;
	}

	int CompareVersions(std::string first, std::string second)
	{
		std::vector<std::string> firstVector = splitVersion(first);
		std::vector<std::string> secondVector = splitVersion(second);

		// Conditions for determining the greatest:
		// 1) The meaning of the first is Number, and the second is Letter
		// 2) The value of the first is greater than the second
		// 3) The number of values of the first is greater than the second

		size_t i = 0;
		size_t firstSize = firstVector.size(), secondSize = secondVector.size();
		char firstChar, secondChar;

		while (i < std::min(firstSize, secondSize))
		{
			firstChar = firstVector[i][0];
			secondChar = secondVector[i][0];

			if (isdigit(firstChar) && !isdigit(secondChar))
			{
				// The first numeric is greater than the second literal
				return 1;
			}
			else if (!isdigit(firstChar) && isdigit(secondChar))
			{
				// The first literal is less than the second numeric
				return -1;
			}
			else if (isdigit(firstChar) && isdigit(secondChar))
			{
				// Comparison of numeric values
				if (stoi(firstVector[i]) > stoi(secondVector[i]))
				{
					return 1;
				}
				else if (stoi(firstVector[i]) < stoi(secondVector[i]))
				{
					return -1;
				}
			}
			else if (!isdigit(firstChar) && !isdigit(secondChar))
			{
				// Comparison of literal values
				if (firstVector[i].compare(secondVector[i]) > 0)
				{
					return 1;
				}
				else if (firstVector[i].compare(secondVector[i]) < 0)
				{
					return -1;
				}
			}

			++i;
		}

		// Comparison by number of elements
		if (firstSize > secondSize)
		{
			return 1;
		}
		else if (firstSize < secondSize)
		{
			return -1;
		}

		return 0;
	}

	nlohmann::json loadJson(const std::string branch, const std::string arch)
	{
		CURL *curl;
		CURLcode res;
		std::string readBuffer;

		curl = curl_easy_init(); // returns a CURL easy handle

		if (curl && !branch.empty() && !arch.empty())
		{
			std::string query = branch + "?arch=" + arch;
			std::string url =
				"https://rdb.altlinux.org/api/export/branch_binary_packages/" + query;
			curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
			res = curl_easy_perform(curl);

			curl_easy_cleanup(curl); // close connection

			if (res != CURLE_OK)
			{
				fprintf(stderr, "curl_easy_perform() failed: %s\n",
						curl_easy_strerror(res));
			}
			else
			{
				return nlohmann::json::parse(readBuffer);
			}
		}
		return 0;
	}

	nlohmann::json comparing(const nlohmann::json &source, const nlohmann::json &target)
	{
		std::string difference;
		nlohmann::json result(nlohmann::json::value_t::array);

		switch (source.type())
		{
		case nlohmann::json::value_t::array:
		{
			//  first pass: traverse common elements
			size_t i = 0, j = 0;
			nlohmann::json temp_missing, temp_extra, temp_updated;

			// get diffrance packages
			while (i < source.size() && j < target.size())
			{
				if (source[i]["name"] > target[j]["name"])
				{
					// extra packages
					++j;
				}
				else if (source[i]["name"] < target[j]["name"])
				{
					// missing packages
					temp_extra.push_back(source[i]);

					++i;
				}
				else
				{

					// updated packages
					std::string versionSource = source[i]["version"];
					std::string versionTarget = target[j]["version"];
					if (CompareVersions(versionSource, versionTarget) == 1)
					{
						temp_updated.push_back(source[i]);
					}
					++i;
					++j;
				}
			}

			while (i < source.size())
			{

				++i;
			}
			while (j < target.size())
			{
				// missing packages
				temp_missing.push_back(target[j]);
				++j;
			}

			result.insert(result.end(), {"missing", temp_missing});
			result.insert(result.end(), {"extra", temp_extra});
			result.insert(result.end(), {"updated", temp_updated});

			break;
		}
		case nlohmann::json::value_t::object:
		{
			//  first pass: traverse this object's elements
			for (auto it = source.cbegin(); it != source.cend(); ++it)
			{
				if (target.find(it.key()) != target.end())
				{
					auto temp_json = comparing(it.value(), target[it.key()]);

					// is not 0 temporary json (only true)
					if (temp_json.size())
					{
						result.insert(result.end(), temp_json.begin(), temp_json.end());
					}
				}
				else
				{
					std::cerr << "found a key that is not in o -> remove it \n";
				}
			}

			break;
		}
		case nlohmann::json::value_t::null:
		case nlohmann::json::value_t::string:
		case nlohmann::json::value_t::boolean:
		case nlohmann::json::value_t::number_integer:
		case nlohmann::json::value_t::number_unsigned:
		case nlohmann::json::value_t::number_float:
		case nlohmann::json::value_t::binary:
		case nlohmann::json::value_t::discarded:
		default:
		{
			break;
		}
		}

		return result;
	}

}
