#include <netdb.h>
#include <sys/socket.h>
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