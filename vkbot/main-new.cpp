//#include <boost/program_options.hpp>
//namespace po = boost::program_options;

#include <iostream>
#include <iterator>
#include <fstream>
#include "https.h"
// #include <glib.h>
// #include <boost/asio.hpp>
// #include <boost/asio/ssl.hpp>
int main(int ac, char* av[])
{
    std::string tokenFileName = "./token";
    std::ifstream tokenFile;
    tokenFile.open(tokenFileName);

    char tokenFileContents[100];
    tokenFile.getline(tokenFileContents, 100);
    // std::cout << tokenFileContents << std::endl;
//////////////////////////////////////////////////////////////////
    //Теперь у нас есть токен из файла. Нда.
//////////////////////////////////////////////////////////////////
    https * httpsObject = new https;
    httpsObject->request("example.com", "");
    // httpsObject->request("vk.com", "");






    ;return 0;
}
