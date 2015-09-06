#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
//#include <unistd.h>
#include <sys/sendfile.h>

#define DEBUG
#define DEBUG_FUCKN
#define DEBUG_GETHOST
struct linkStruct
{
	std::string protocol;
	std::string hostname;
	std::string relative;
	std::string filename;
};
struct requestSkeleton
{
	std::string method = "GET";
	char SP = char(32);
	std::string httpVer = "HTTP/1.1";
	std::string requestHeader = "\r\nAccept: */*\r\nAccept-Charset: utf-8";
	std::string CRLF = "\r\n\r\n";
	int flags = 0;
};

void show_help(char* cmdname);
int gethost(char* address, linkStruct *result);
void log(std::string message);


int main (int argc, char* argv[])
{

	if (argc < 2) {

		fprintf(stderr, "%i : %s\n", argc, argv[argc - 1]);
		show_help(argv[0]);
		//argv[1] = "http://vk.com/doc12560157_378499337";
		argc += 1;
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

	linkStruct addr;

	temporaryInteger = gethost(argv[temporaryInteger], &addr);


	if(temporaryInteger != 0)
		return temporaryInteger;



	struct addrinfo *he = new struct addrinfo;

	he->ai_socktype = SOCK_STREAM;
	he->ai_family = AF_INET;

    temporaryInteger = getaddrinfo (addr.hostname.c_str(), "80", he, &he);
#	ifdef DEBUG
    log ("getaddrinfo done: " + std::to_string(temporaryInteger));
#	endif
    if(temporaryInteger != 0) {
    	//return temporaryInteger;
    	temporaryInteger = getaddrinfo(addr.hostname.c_str(), "80", NULL, &he);
    	log("getaddrinfo done[+1]: " + std::to_string(temporaryInteger));
    }

    log("SOCK_DGRAM = " + std::to_string(SOCK_DGRAM));



    struct addrinfo * temporaryPointer = he;
  //  {
#		ifdef DEBUG_FUCKN
    	log("he->ai_socktype = " + std::to_string(he->ai_socktype));

	struct sockaddr_in *tempinadr =  (struct sockaddr_in *)he->ai_addr;

    log("struct addrinfo {\
    \nint     ai_flags;			" + std::to_string(he->ai_flags) +\
    "\nint     ai_family;			" + std::to_string(he->ai_family) +\
    "\nint     ai_socktype;			" + std::to_string(he->ai_socktype) +\
    "\nint     ai_protocol;			" + std::to_string(he->ai_protocol) +\
    "\nsize_t  ai_addrlen;			" + std::to_string(he->ai_addrlen) +\
    "\nstruct  sockaddr *ai_addr;	" + std::to_string(he->ai_addr->sa_family) + "  " + inet_ntoa(tempinadr->sin_addr));

    log("char    *ai_canonname;     /* canonical name */" \
    "\nstruct  addrinfo *ai_next; /* this struct can form a linked list */" /*+ std::to_string(he->ai_next) +*/\
    "\n}");

#    	endif

    //	he = he->ai_next;
   // } while (he->ai_socktype != SOCK_DGRAM && temporaryPointer != he && true);
 	/*if (he == NULL)
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
    }*/
#	ifdef DEBUG
	log("he->ai_socktype = " + std::to_string(he->ai_socktype));
    log ("resolved to " + std::string(he->ai_addr->sa_data));
#	endif
    delete  temporaryPointer;
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

#	ifdef DEBUG
    log("Binding socketFd = " + std::to_string(socketFd));
#	endif

   /* temporaryInteger = bind(socketFd, he->ai_addr, he->ai_addrlen);
    if(temporaryInteger != 0) {
    	log("Bind error: " + temporaryInteger);
    	return temporaryInteger;
    }*/

#	ifdef DEBUG
    log("Binded socketFd = " + std::to_string(socketFd));
#	endif

    //std::string request;
    if (addr.protocol != "http") {
    	log("protocol егор");
    	return 15;
    }
    log("he->ai_addr->sa_data = " + std::string(he->ai_addr->sa_data));

    log("Trying to connect..");
    temporaryInteger = connect(socketFd, he->ai_addr, he->ai_addrlen);
    log("connected; return value: " + std::to_string(temporaryInteger));
    if (temporaryInteger != 0) {
    	log ("connection error, exitting");
    	return 50;
    }


    //////////////////////////////////////////////////
    //Connection established. It's time to send data! ^.^
    std::string message = "";
    requestSkeleton requestSkeleton;
    message = requestSkeleton.method + requestSkeleton.SP + addr.relative + requestSkeleton.SP + requestSkeleton.requestHeader
    		+ requestSkeleton.SP + requestSkeleton.httpVer + requestSkeleton.CRLF;
   // message = "GET  	/doc12560157_378499337  	HTTP/1.1\r\n\r\n";
    log(message);

    temporaryInteger = send(socketFd, message.c_str(), message.size(), 0);
    log("Sent data: " + std::to_string(temporaryInteger));
    log("Trying to open file: " + std::string("./wget_" + addr.filename) + "\n...");
    FILE * localFd = fopen(std::string("./wget_" + addr.filename).c_str(), "wb+");
    //temporaryInteger = recv();
    if (localFd == NULL) {
    	log("Error opening localFd");
    	return 100;
    }
    log("Success.");
    char  server_reply[2000];
    temporaryInteger = recv(socketFd, server_reply, 2000, 0);
    log("received data: " + std::to_string(temporaryInteger));
    log(server_reply);
    fprintf(localFd, "%s\n", server_reply);



	return 0;
}




void show_help(char* cmdname) {
	fprintf(stdout, "A simple wget implementation\n" );
	fprintf(stdout, "Usage: %s ADDRESS\n", cmdname );
}




int gethost(char* address, linkStruct * result) {
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
	end = s.find("?", temp) - 1;
	if(temp != s.npos)
	{
		result->filename = s.substr(temp + 1, abs(end - temp));
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