// #include <netdb.h>
// #include <sys/socket.h>
#include <iostream>
#include <curl/curl.h>
#include <cstring>
class https
{
public:
    https();
    ~https();
    int request(std::string, std::string);
private:
    size_t WriteMemoryCallback(char *, size_t, size_t, void *);
    struct BufferStruct
    {
        char * buffer;
        size_t size;
    };

    CURL *curl;
    CURLcode res;
};