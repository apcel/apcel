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


    vkapi * vkapiObject = new vkapi;
    vkapiObject->groupsGetById("1");

    ; return 0;
}

    //access_token=98a9164bfdc63abc1752bccfd0765d4d34e1b72159a5faf4d3577184db9fef517e38d440a1fc80c8e8148
    //https://api.vk.com/messages.send?domain=exxenon&message="test from api 2"
    //https://api.vk.com/method/messages.send?domain=apcel&message=%22test%20from%20api%202%22&access_token=98a9164bfdc63abc1752bccfd0765d4d34e1b72159a5faf4d3577184db9fef517e38d440a1fc80c8e8148

