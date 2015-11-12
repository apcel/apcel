//#include <boost/program_options.hpp>
//namespace po = boost::program_options;

#include <iostream>
#include <iterator>
#include <fstream>
// #include <glib.h>

int main(int ac, char* av[])
{
    std::string tokenFileName = "../example-config.ini";
    std::ifstream tokenFile;
    tokenFile.open(tokenFileName);

    char tokenFileContents[50];

    std::cout << tokenFile.getline(tokenFileContents, 50) << std::endl;

    return 0;
}
