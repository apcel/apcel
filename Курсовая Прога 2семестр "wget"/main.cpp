#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <iostream>


#define DEBUG


void show_help(char* cmdname);
std::string gethost(char* address, int *begin, int *end);
void log(std::string message);

int main (int argc, char* argv[])
{

	if (argc < 2) {

		fprintf(stderr, "%i : %s\n", argc, argv[argc - 1]);
		show_help(argv[0]);
		return -1;
	}

	int temporaryInteger = 0;

	//struct hostent *he;

	int endOfHostPosition = 0;
	int beginOfHostPosition = 0;
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

	std::string hostname = gethost(argv[temporaryInteger], &beginOfHostPosition, &endOfHostPosition);



	struct addrinfo * he;

    getaddrinfo (hostname.c_str(), NULL, NULL,&he);
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
    log ("resolved to " + std::string(he->ai_addr->sa_data));
    ////////////////////////////////////////////////////
    //Итак, мы имеем адрес хоста из ссылки. Мда.
#	endif






	return 0;
}





void show_help(char* cmdname) {
	fprintf(stdout, "A simple wget implementation\n" );
	fprintf(stdout, "Usage: %s ADDRESS\n", cmdname );
}
#define DEBUG_GETHOST
std::string gethost(char* address, int *begin, int *end) {
	*begin = 0;
	std::string s = address;
	*end = s.size() / sizeof(char);
	int temp = 0;
	temp = s.find("//", 0);
	if (temp != s.npos)
		*begin = temp + 2;
	temp = s.find("/", *begin + 1);
	if (temp != s.npos)
		*end = temp;
#	ifdef DEBUG_GETHOST
	log("gethost returns:");
	log("*begin = " + std::to_string(*begin));
	log("*end   = " + std::to_string(*end));
	log("ukhm, host may be the \'" + s.substr(*begin, abs(*end - *begin)) + "\'");
#	endif
	s = s.substr(*begin, abs(*end - *begin));
	return s;
}

void log(std::string  message) {
#	ifdef DEBUG
	fprintf(stdout, "%s\n", message.c_str());
#	endif
}