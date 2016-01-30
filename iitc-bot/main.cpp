#include <iostream>
#include <cpr/cpr.h>
#include <fstream>
#include <iostream>

#include "rapidjson/document.h"
#include "iitc.h"
// #include "rapidjson/stringbuffer.h"

rapidjson::Document loadSettings(std::string fileName) {
    std::ifstream jsonSettingsFile(fileName);
    std::string jsonSettings((std::istreambuf_iterator<char>(jsonSettingsFile)),
                             std::istreambuf_iterator<char>());
    rapidjson::Document d;
    d.Parse(jsonSettings.c_str());
    if ( !d.IsObject()) {
        std::cerr << "Troubles with parsing json settings in '" + fileName + "'"  << std::endl
                  << "Please ensure it is a correct json object" << std::endl;
        exit(1);
    };
    return d;
}



int main(int argc, char** argv) {
    rapidjson::Document settings = loadSettings("jsonSettingsFile.json");
    iitc iitc(settings["cookieSACSID"].GetString(), settings["headerCSRF"].GetString(), settings["cookieCSRF"].GetString());
    rapidjson::Document response = iitc.request("getPortalDetails", "");
    std::cout << response["result"][1].GetString() << std::endl;
    // std::cout << response.text << std::endl;
    return 0;
}