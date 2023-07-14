#include "main.h"

using namespace std;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

int main(void)
{
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init(); // returns a CURL easy handle
    
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, "https://rdb.altlinux.org/api/export/branch_binary_packages/p10?arch=x86_64");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl); // close connection
        
        if (res != CURLE_OK){
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }else{
            std::cout << readBuffer << std::endl;
        }
		        
    }
    return 0;
}