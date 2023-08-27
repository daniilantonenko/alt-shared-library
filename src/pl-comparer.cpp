#include <pl-comparer/pl-comparer.h>

using json = nlohmann::json;

namespace PackageListComparer
{

	static size_t WriteCallback(void *contents, size_t size, size_t nmemb,
								void *userp)
	{
		((std::string *)userp)->append((char *)contents, size * nmemb);
		return size * nmemb;
	}

	json loadJson(std::string arch)
	{
		CURL *curl;
		CURLcode res;
		std::string readBuffer;

		curl = curl_easy_init(); // returns a CURL easy handle

		if (curl && !arch.empty())
		{
			std::string query = "p10?arch=" + arch;
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
				return json::parse(readBuffer);
			}
		}
		return 0;
	}

	// Json Simplification (join by same keys value "op")
	json simpler(const json &source)
	{
		json result;

		// Search by key - value
		for (auto &element : source.items())
		{
			const auto &key = element.value();

			/*std::cout << "=========\t" << key.is_structured() << " - " << key.is_primitive() << " - " << key.is_object() << " - " << key.size() << "\t =========\t\n"
			 << std::endl;
			std::cout << "=========\t" << std::setw(2) << key << std::endl;*/

			// key = key.unflatten();

			// Check the structure and content of the desired key "op" and "path"
			if (key.is_structured() && key.contains("op") && key.contains("path"))
			{

				// Get pointer
				std::string operation = key["op"];
				const char *pointerOperation = const_cast<char *>(operation.c_str());

				// Get path
				auto path = key["path"];

				// Get value
				auto value = key["value"];

				if (key.contains("value"))
				{
					// NOTE do a recursive pass ?
					// std::cout << std::setw(2) << path << " | " << value << std::endl;

					// Insert key with value
					auto jsonData = json::object_t::value_type(path, value);
					// json jsonData = {"path", "value"};

					result[pointerOperation].push_back(jsonData);
				}
				else
				{
					// Insert key without value
					result[pointerOperation].push_back(path);
				}
			}
		}

		// result.unflatten();

		return result;
	}

	json comparing(const json &source, const json &target)
	{
		std::string difference;
		json result(json::value_t::array);

		switch (source.type())
		{
		case json::value_t::array:
		{
			//  first pass: traverse common elements
			size_t i = 0, j = 0;
			json temp_json;

			// get diffrance packages
			while (i < source.size() && j < target.size())
			{
				if (source[i]["name"] < target[j]["name"])
				{
					// missing packages
					difference = "missing";
					if (difference != "updated")
					{
						temp_json.push_back(source[i]);
					}
					++i;
				}
				else if (source[i]["name"] > target[j]["name"])
				{
					// extra packages
					difference = "extra";
					++j;
				}
				else
				{
					if ((source[i]["version"] != target[j]["version"]))
					{
						std::cout << source[i].dump(4) << "\n";
						std::cout << target[j].dump(4) << "\n";
					}

					difference = "updated";

					// common packages
					if (difference == "updated" && source[i]["version"] > target[j]["version"])
					{
						temp_json.push_back(source[i]);
					}
					++i;
					++j;
				}
			}

			while (i < source.size())
			{
				temp_json.push_back(source[i]);
				++i;
			}

			result.push_back({{difference, temp_json}});

			break;
		}
		case json::value_t::object:
		{
			//  first pass: traverse this object's elements
			for (auto it = source.cbegin(); it != source.cend(); ++it)
			{
				if (target.find(it.key()) != target.end())
				{
					auto temp_json = comparing(it.value(), target[it.key()]);
					result.insert(result.end(), temp_json.begin(), temp_json.end());
				}
				else
				{
					std::cerr << "found a key that is not in o -> remove it \n";
				}
			}

			break;
		}
		case json::value_t::null:
		case json::value_t::string:
		case json::value_t::boolean:
		case json::value_t::number_integer:
		case json::value_t::number_unsigned:
		case json::value_t::number_float:
		case json::value_t::binary:
		case json::value_t::discarded:
		default:
		{
			break;
		}
		}

		return result;
	}

	Comparator::Comparator() {}
	Comparator::Comparator(std::string first, std::string second)
		: patch(json::diff(loadJson(first), loadJson(second))) {}

	json Comparator::getThisJson() { return this->patch; }

}
