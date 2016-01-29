#include <iostream>
#include <cpr/cpr.h>


#include "rapidjson/document.h"
#include "iitc.h"
// #include "rapidjson/stringbuffer.h"

int main(int argc, char** argv) {

    iitc iitc;
    rapidjson::Document response = iitc.request("getPortalDetails", "");
    std::cout << response["result"][1].GetString() << std::endl;
    // std::cout << response.text << std::endl;
    return 0;
}