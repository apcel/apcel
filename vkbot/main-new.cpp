//#include <boost/program_options.hpp>
//namespace po = boost::program_options;

#include <iostream>
#include <iterator>
#include <fstream>
#include "https.h"
#include "vkapi.h"
// #include <glib.h>
// #include <boost/asio.hpp>
// #include <boost/asio/ssl.hpp>
int main(int ac, char* av[])
{

    // std::cout << tokenFileContents << std::endl;
//////////////////////////////////////////////////////////////////
    //Теперь у нас есть токен из файла. Нда.
//////////////////////////////////////////////////////////////////
    https * httpsObject = new https;
    // httpsObject->request("example.com", "");
    // httpsObject->request("vk.com", "");

    // fprintf(stderr, "%s\n", "=====================================================");

    // httpsObject->request("https://api.vk.com/method/messages.send?domain=apcel&message=%22test%20from%20api%202%22&access_token=98a9164bfdc63abc1752bccfd0765d4d34e1b72159a5faf4d3577184db9fef517e38d440a1fc80c8e8148");
    // httpsObject->getResponse();


    httpsObject->~https();
    ; return 0;
}
