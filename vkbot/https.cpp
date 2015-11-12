#include "https.h"
https::https() {

};

struct https::linkStruct
{
    std::string protocol = "";
    std::string hostname = "";
    std::string relative = "";
    std::string filename = "";
};

struct https::requestSkeleton
{
    std::string method = "GET";
    char SP = char(32);
    std::string httpVer = "HTTP/1.1";
    std::string requestHeader = "\r\nAccept: */*\r\nAccept-Charset: utf-8\r\nConnection: Keep-Alive\r\n";
    std::string CRLF = "\r\n\r\n";
    int flags = 0;
};