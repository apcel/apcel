//#include <boost/program_options.hpp>
//namespace po = boost::program_options;

#include <iostream>
#include <iterator>
#include <fstream>
// #include <glib.h>

int main(int ac, char* av[])
{
    std::string tokenFileName = "./token";
    std::ifstream tokenFile;
    tokenFile.open(tokenFileName);

    char tokenFileContents[100];
    tokenFile.getline(tokenFileContents, 100);
    std::cout << tokenFileContents << std::endl;

    return 0;
}
