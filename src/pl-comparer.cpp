#include <pl-comparer/pl-comparer.h>

using json = nlohmann::json;

namespace PackageListComparer {

static size_t WriteCallback(void *contents, size_t size, size_t nmemb,
														void *userp) {
	((std::string *)userp)->append((char *)contents, size * nmemb);
	return size * nmemb;
}

int compare(std::string arch) {
	auto text = R"(
		{
			"Image": {
				"Width":  800,
				"Height": 600,
				"Title":  "View from 15th Floor",
				"Thumbnail": {
					"Url":    "http://www.example.com/image/481989943",
					"Height": 125,
					"Width":  100
				},
				"Animated" : false,
				"IDs": [116, 943, 234, 38793]
			}
		}
		)";

	CURL *curl;
	CURLcode res;
	std::string readBuffer;

	curl = curl_easy_init(); // returns a CURL easy handle

	if (curl && !arch.empty()) {
		std::string query = "p10?arch=" + arch;
		std::string url =
				"https://rdb.altlinux.org/api/export/branch_binary_packages/" + query;
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		res = curl_easy_perform(curl);

		curl_easy_cleanup(curl); // close connection

		if (res != CURLE_OK) {
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
							curl_easy_strerror(res));
		} else {
			// std::cout << readBuffer << std::endl;
			auto j = json::parse(text);
			// std::cout << j.dump(2) << '\n';

			return 0;
		}
	}
	return 0;
}

Comparator::Comparator() {}
Comparator::Comparator(int id, std::string const &name) : m_id(id), m_name(name) {}
Comparator::Comparator(json data) : m_id(data["id"]), m_name(data["name"]) {}
Comparator::Comparator(json first, json second)
		: endresult(json::diff(first, second)) {}

json Comparator::getJson() {
	json Comparator;
	Comparator["id"] = m_id;
	Comparator["name"] = m_name;

	return Comparator;
}
json Comparator::compare(json first, json second) {
	json result;
	result = json::diff(first, second);

	return result;
}
json Comparator::getThisJson() { return this->endresult; }

} // namespace PackageListComparer
