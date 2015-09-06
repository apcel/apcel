#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>

#define DEBUG

struct link
{
	std::string protocol;
	std::string hostname;
	std::string relative;
	std::string filename;
};
struct request
{
	std::string method;
	char SP = char(32);
};

void show_help(char* cmdname);
int gethost(char* address, link *result);
void log(std::string message);


int main (int argc, char* argv[])
{

	if (argc < 2) {

		fprintf(stderr, "%i : %s\n", argc, argv[argc - 1]);
		show_help(argv[0]);
		//argv[1] = "google.com";
		return -1;
	}

	int temporaryInteger = 1;

	//struct hostent *he;

	//int endOfHostPosition = 0;
	//int beginOfHostPosition = 0;
	for (int i = 1; i < argc; i++)
	{
		std::string s = argv[i];
		if (s.find("/") != s.npos)
		{
			//fprintf(stdout, "found link-like argument \"%s\"\n", argv[i] );
			temporaryInteger = i;
		}
	}
#	ifdef DEBUG
	fprintf(stdout, "found link-like %s\n", argv[temporaryInteger]);
#	endif

	link addr;

	temporaryInteger = gethost(argv[temporaryInteger], &addr);


	if(temporaryInteger != 0)
		return temporaryInteger;



	struct addrinfo * he;

    temporaryInteger = getaddrinfo (addr.hostname.c_str(), NULL, NULL,&he);
#	ifdef DEBUG
    log ("getaddrinfo done");
#	endif
    if(temporaryInteger != 0)
    	return temporaryInteger;


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
        return 1;
    }

#	ifdef DEBUG
    //log ("resolved to " + std::string(he->ai_addr->sa_data));
#	endif
    ////////////////////////////////////////////////////
    //So we have host adress from link.
    int socketFd;
    socketFd = socket(he->ai_family, he->ai_socktype, he->ai_protocol);
#	ifdef DEBUG
    log("socketFd = " + std::to_string(socketFd));
#	endif
    if(socketFd < 0)
    {
    	fprintf(stderr, "Error opening socketFd: %i\n", socketFd);
    	return 2;
    }

    temporaryInteger = bind(socketFd, he->ai_addr, he->ai_addrlen);
    if(temporaryInteger != 0)
    	return temporaryInteger;

#	ifdef DEBUG
    log("Binded socketFd = " + std::to_string(socketFd));
#	endif

    //std::string request;




	return 0;
}




void show_help(char* cmdname) {
	fprintf(stdout, "A simple wget implementation\n" );
	fprintf(stdout, "Usage: %s ADDRESS\n", cmdname );
}


#define DEBUG_GETHOST

int gethost(char* address, link * result) {
	int begin = 0;
	std::string s = address;
	int end = s.size() / sizeof(char);
	int temp = 0;
	temp = s.find("//", 1);
	if (temp != s.npos)
	{
		begin = temp + 2;
		result->protocol = s.substr(0, temp - 1);
	} else {
		temp = 0;
		result->protocol = "http";
	}
	temp = s.find("/", begin + 1);
	if (temp != s.npos)
	{
		end = temp;
		result->hostname = s.substr(begin, abs(end - begin));
		result->relative = s.substr(end);
	}
	temp = s.rfind("/");
	if(temp != s.npos)
	{
		result->filename = s.substr(temp + 1);
	} else {
		return -2;
	}


	//s = s.substr(begin, abs(end - begin));
#	ifdef DEBUG_GETHOST
	log("gethost returns:");
	log("begin = " + std::to_string(begin));
	log("end   = " + std::to_string(end));
	//log("ukhm, host may be the \'" + s + "\'");
	log("result->protocol = " + result->protocol);
	log("result->hostname = " + result->hostname);
	log("result->relative = " + result->relative);
	log("result->filename = " + result->filename);
#	endif

//	return s;
	return 0;
}
//http://img2-ak.lst.fm/i/u/174s/85f037ecf5ed4b7bcb94b79ef139c385.gif

void log(std::string  message) {
#	ifdef DEBUG
	fprintf(stdout, "%s\n", message.c_str());
#	endif
}