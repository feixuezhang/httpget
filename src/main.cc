#include <stdio.h>
#include <curl/curl.h>
#include <string>
#include <iostream>

size_t writeToString(void *ptr, size_t size, size_t count, void *stream)
{
    ((std::string*)stream)->append((char*)ptr, 0, size* count);
    return size* count;
}

int main(void)
{
  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  if(curl) {
    const std::string url = "url";
    std::string data;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeToString);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
    // data now holds response

    // write curl response to string variable..
    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    std::cout << data << std::endl;

    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  return 0;
}
