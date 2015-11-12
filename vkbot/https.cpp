#include "https.h"
https::https() {
    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "%s\n", "failed to init curl");
    };
   
};
https::~https() {
    curl_easy_cleanup(curl);
    curl_global_cleanup();
    fprintf(stdout, "%s\n", "destructor");
}
int https::request(std::string method, std::string response) {
    this->method = method;
    setup();


    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if (res != CURLE_OK)
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));

}


void https::setup() {
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback); // Passing the function pointer to LC
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&output); // Passing our BufferStruct to LC
    curl_easy_setopt(curl, CURLOPT_URL, method.c_str());
}




// This is the function we pass to LC, which writes the output to a BufferStruct
size_t https::WriteMemoryCallback(char *ptr, size_t size, size_t nmemb, void *data)
{
    size_t realsize = size * nmemb;

    struct BufferStruct * mem = (struct BufferStruct *) data;

    mem->buffer = (char*)realloc(mem->buffer, mem->size + realsize + 1);

    if ( mem->buffer ) {
        memcpy( &( mem->buffer[ mem->size ] ), ptr, realsize );
        mem->size += realsize;
        mem->buffer[ mem->size ] = 0;
    }
    return realsize;
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