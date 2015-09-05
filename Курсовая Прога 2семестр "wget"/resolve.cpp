
#include <stdio.h>

#ifdef _WIN32
#  include "winsock.h"
#else
#  include <netdb.h>
#  include <arpa/inet.h>
#endif



int resolve (char *argv[])
{
    struct hostent *he;

    if (argc == 1)
        return -1;

 

    he = gethostbyname (argv[0]);
    if (he == NULL)
    {
        switch (h_errno)
        {
            case HOST_NOT_FOUND:
                fputs ("The host was not found.\n", stderr);
                break;
            case NO_ADDRESS:
                fputs ("The name is valid but it has no address.\n", stderr);
                break;
            case NO_RECOVERY:
                fputs ("A non-recoverable name server error occurred.\n", stderr);
                break;
            case TRY_AGAIN:
                fputs ("The name server is temporarily unavailable.", stderr);
                break;
        }
    }
    else
    {
        puts (inet_ntoa (*((struct in_addr *) he->h_addr_list[0])));
    }

    uninitialise ();

    return he != NULL;
}