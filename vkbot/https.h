#include <netdb.h>
#include <sys/socket.h>
#include <iostream>
class https
{
public:
    https();
    ~https();
private:
    struct addrinfo *he;
    struct requestSkeleton;
    struct linkStruct;
    int socketFd;
    int tempInt;
};