#include <iostream>
#include <cpr/cpr.h>
#include <fstream>
#include <iostream>

#include "rapidjson/document.h"
#include "iitc.h"
#include "portal.h"
// #include "rapidjson/stringbuffer.h"

rapidjson::Document parceJSONFromFile(std::string fileName) {
    std::ifstream jsonSettingsFile(fileName);
    std::string jsonSettings((std::istreambuf_iterator<char>(jsonSettingsFile)),
                             std::istreambuf_iterator<char>());
    rapidjson::Document d;
    d.Parse(jsonSettings.c_str());
    if (d.HasParseError()) {
        std::cerr << "Troubles with parsing json settings in '" + fileName + "'"  << std::endl
                  << "Please ensure it is a correct json object" << std::endl;
        exit(1);
    };
    return d;
}



int main(int argc, char** argv) {
    // rapidjson::Document settings = parceJSONFromFile("jsonSettingsFile.json");
    // iitc iitc(settings["cookieSACSID"].GetString(), settings["headerCSRF"].GetString(), settings["cookieCSRF"].GetString());
    // rapidjson::Document response = iitc.request("getPortalDetails", "");
    // std::cout << response["result"][1].GetString() << std::endl;
    // std::cout << response.text << std::endl;
    portal portal;
    rapidjson::Document portalJSON1 = parceJSONFromFile("out.json");
    rapidjson::Document portalJSON2 = parceJSONFromFile("portal.json");

    // if(!portal.parseJSON(&portalJSON))
    //     std::cout << "Error while parsing" << std::endl;
    if(portal.parseJSON(&portalJSON1)){};
    if(portal.parseJSON(&portalJSON2)){};
    return 0;
}