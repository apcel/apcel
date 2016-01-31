#include <iostream>
#include <cpr/cpr.h>
#include <fstream>
#include <iostream>

#define RAPIDJSON_NOMEMBERITERATORCLASS
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
    // portal portal;
    rapidjson::Document territoryJSON = parceJSONFromFile("territory.json");
    // rapidjson::Document portalJSON2 = parceJSONFromFile("portal.json");

    // if(!portal.parseJSON(&portalJSON))
    //     std::cout << "Error while parsing" << std::endl;
    // if(portal.parseJSON(&portalJSON1)){};


    std::vector<std::vector<portal *>*> *map = new std::vector<std::vector<portal *>*> ;
    std::vector<portal *> *chunk = new std::vector<portal *>;
    portal * entity = new portal();
    rapidjson::Value & mapJSON = territoryJSON["result"]["map"];
    for (rapidjson::Value::MemberIterator chunkJSON = mapJSON.MemberBegin();
            chunkJSON != mapJSON.MemberEnd(); ++chunkJSON) {
        chunk->clear();
        rapidjson::Value & temp = chunkJSON->value;
        std::string asdf = chunkJSON->name.GetString();
        for (rapidjson::Value::MemberIterator entityJSON = temp.MemberBegin();
                entityJSON != temp.MemberEnd(); ++entityJSON) {
            rapidjson::Value  & entities = entityJSON->value;
            for (int i = 0; i < entities.Size(); i++) {
                rapidjson::Value & tempValue = entities[i];
                if (entity->parseJSON( & tempValue )) {
                    chunk->push_back(entity);
                    entity = new portal();
                };
            };
        };
        std::cout << "#####################################################" << std::endl;
        if (!chunk->empty()) {
            std::cout << chunk->size() << "\tportals in " << asdf << std::endl;
            map->push_back(chunk);
            std::cout << "Portals: " << std::endl;
            for(auto i : *chunk) {
                i->printData();
                std::cout << "===================================================" << std::endl;
            }
        } else {
            std::cerr << "No\tportals in " << asdf << std::endl;
        }
    };
    // for (auto chunks : *map)

        return 0;
}