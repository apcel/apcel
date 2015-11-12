#include <netdb.h>
#include <sys/socket.h>
#include <iostream>
class https
{
public:
    https();
    ~https();
    void * request();
private:
    struct requestSkeleton{
        std::string method = "GET";
        char SP = char(32);
        std::string httpVer = "HTTP/1.1";
        std::string requestHeader = "\r\nAccept: */*\r\nAccept-Charset: utf-8\r\nConnection: Keep-Alive\r\n";
        std::string CRLF = "\r\n\r\n";
        int flags = 0;
    };
    struct linkStruct{
        std::string protocol = "";
        std::string hostname = "";
        std::string method = "";
        std::string filename = "";
    };
    struct addrinfo *he;
    requestSkeleton requestSkeletonEntity;
    linkStruct linkStructEntity;
    int socketFd;
    int tempInt;
};