#include <iostream>
#include <cpr/cpr.h>
#include <fstream>
#include <iostream>
#include <time.h>
#include "rapidjson/document.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/prettywriter.h"
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
void saveJSONToFile(rapidjson::Document *JSON, std::string file) {
    rapidjson::StringBuffer buffer;
    // rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    // rapidjson::FileWriteStream
    // buffer.Reserve(JSON.Size());
    FILE * output = fopen(file.c_str(), "w");
    if (!output) {
        std::ofstream fileCreator(file);
        fileCreator << "";
        fileCreator.clear();
        output = fopen(file.c_str(), "w");
    }
    char writeBuffer[65536];
    rapidjson::FileWriteStream os(output, writeBuffer, sizeof(writeBuffer));
    rapidjson::PrettyWriter<rapidjson::FileWriteStream> writer(os);
    JSON->Accept(writer);
}


int main(int argc, char** argv) {

    // rapidjson::Document settings = parceJSONFromFile("jsonSettingsFile.json");
    // std::string settingsFileName = "jsonSettingsFile.json";
    // iitc iitc(settingsFileName);
    // time_t asdf = iitc.GMTtoUNIX(std::string(settings["expires"].GetString()));




    // rapidjson::Document portalJson = parceJSONFromFile("portal.json");
    rapidjson::Document fullPortalJson = parceJSONFromFile("jsons/out.json");
    portal portalObject(fullPortalJson["result"]);
    portalObject.printData();
    std::cout << std::endl;


    exit(0);
}
#ifdef RANDOM_STRING_NOT_DEFINED

    short zoom = 15;
    std::string titlekeys =
        iitc.pointToTileId(
            iitc.lngToTile(37829358, iitc.TILES_PER_EDGE[zoom]),
            iitc.latToTile(55775830, iitc.TILES_PER_EDGE[zoom]),
            zoom,
            0
        );
    std::cout << titlekeys << std::endl;
    std::string params = "{\"tileKeys\": [\"" + titlekeys + "\"],\"v\":\"9ffe0cfdf367c491a20802d3c606d679992e8b08\"}";
    // "{\"tileKeys\":[\"15_19362_10000_0_8_100\",\"15_19362_9999_0_8_100\",\"15_19363_10000_0_8_100\",\"15_19363_9999_0_8_100\",\"15_19361_10000_0_8_100\",\"15_19361_9999_0_8_100\"],\"v\":\"9ffe0cfdf367c491a20802d3c606d679992e8b08\"}";
    // std::cout << params << std::endl;
    // rapidjson::Document response = iitc.request("getEntities", params);
    // std::cout << response["result"][1].GetString() << std::endl;
    // std::cout << response.text << std::endl;
    // portal portal;
    rapidjson::Document territoryJSON = parceJSONFromFile("file.txt");
    // rapidjson::Document portalJSON2 = parceJSONFromFile("portal.json");
    // rapidjson::Document & territoryJSON = response;
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
                // if (entity->parseJSON( & tempValue )) {
                chunk->push_back(entity);
                entity = new portal();
                // };
            };
        };
        std::cout << "#####################################################" << std::endl;
        if (!chunk->empty()) {
            std::cout << chunk->size() << "\tportals in " << asdf << std::endl;
            map->push_back(chunk);
            std::cout << "Portals: " << std::endl;
            for (auto i : *chunk) {
                i->printData();
                std::cout << "===================================================" << std::endl;
            }
        } else {
            std::cerr << "No\tportals in " << asdf << std::endl;
        }
    };
    for (auto chunks : * map) {
        for (auto entities : *chunks)
            delete entities;
        delete chunks;
    };
    rapidjson::Document doc;
    doc.SetObject();
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
    doc.AddMember("map", mapJSON, allocator);
    saveJSONToFile(&doc, "file.txt");
    // for (auto chunks : *map)
    return 0;
}
#endif