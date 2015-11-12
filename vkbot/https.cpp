#include "https.h"
https::https() {
  curl_global_init(CURL_GLOBAL_DEFAULT);

  curl = curl_easy_init();
  if(!curl) {
    fprintf(stderr, "%s\n", "failed to init curl");
  }
};
https::~https() {
  curl_global_cleanup();
}
int https::request(std::string method, std::string response) {
    curl_easy_setopt(curl, CURLOPT_URL, "https://vk.com/");


    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    /* always cleanup */
    curl_easy_cleanup(curl);

}

// class https
// {
// public:
//     https();
//     ~https();
//     void * request();
// private:
//     struct requestSkeleton{
//         std::string method = "GET";
//         char SP = char(32);
//         std::string httpVer = "HTTP/1.1";
//         std::string requestHeader = "\r\nAccept: */*\r\nAccept-Charset: utf-8\r\nConnection: Keep-Alive\r\n";
//         std::string CRLF = "\r\n\r\n";
//         int flags = 0;
//     };
//     struct linkStruct{
//         std::string protocol = "";
//         std::string hostname = "";
//         std::string method = "";
//         std::string filename = "";
//     };
//     struct addrinfo *he;
//     requestSkeleton requestSkeletonEntity;
//     linkStruct linkStructEntity;
//     int socketFd;
//     int tempInt;
// };