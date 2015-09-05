#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <iostream>



void show_help(char* cmdname);



int main (int argc, char* argv[])
{

	if (argc < 2) {

		fprintf(stderr, "%i : %s\n", argc, argv[argc - 1]);
		show_help(argv[0]);
		return -1;
	}

	int temporaryInteger = 0;

	struct hostent *he;

	for (int i = 1; i < argc; i++)
	{
		std::string s = argv[i];
		if (s.find("/")) 
		{
			fprintf(stdout, "found link-like argument \"%s\"\n", argv[i] );
			temporaryInteger = i;
		}
	}

    he = gethostbyname (argv[temporaryInteger]);
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



	return 0;
}





void show_help(char* cmdname) {
	fprintf(stdout, "A simple wget implementation\n" );
	fprintf(stdout, "Usage: %s ADDRESS\n", cmdname );


}