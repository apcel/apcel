#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>




void show_help(char* cmdname);



int main (int argc, char* argv[])
{

	if (argc < 2) {

		fprintf(stderr, "%i : %s\n", argc, argv[argc - 1]);
		show_help(argv[0]);
		return 1;
	}


	return 0;
}





void show_help(char* cmdname) {
	fprintf(stdout, "A simple wget implementation\n" );
	fprintf(stdout, "Usage: %s ADDRESS\n", cmdname );


}