#pragma once
#include "portal.h"
portal::portal() {};
portal::~portal() {};


// void portal::parseJSON(rapidjson::Document * JSON) {
//     bool a = parseJSON(JSON);
// }
void portal::debugJsonErr(rapidjson::Value * JSON) {
#ifdef DEBUG
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    JSON->Accept(writer);
    std::cerr << "For debugging purposes, printing serialized input json:" << std::endl <<
              buffer.GetString() << std::endl;
#endif
}
bool portal::parseJSON(rapidjson::Value * JSON) {
    /*..and save raw portal data*/
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    JSON->Accept(writer);
    raw = buffer.GetString();
    if (JSON->IsObject()) {
        assert(JSON[0].HasMember("result"));
        return parseArray(&JSON[0]["result"]);
    } else {

        assert(parseArray(&JSON[0][2]));


        /**/
        return true;
    }
    return false;
};

bool portal::parseArray(rapidjson::Value * JSON) {
    if (!JSON[0][0].IsString())
        debugJsonErr(&JSON[0]);
    if (std::strncmp(JSON[0][0].GetString(), "p", 1))
        return false;
    this->team = JSON[0][1].GetString();   // printData();
    this->latE6 = JSON[0][2].GetInt();  //    printData();
    this->lngE6 = JSON[0][3].GetUint64(); //   printData();
    this->level = JSON[0][4].GetInt();    //printData();
    this->health = JSON[0][5].GetDouble();  //  printData();
    this->resCount = JSON[0][6].GetInt();    //printData();
    this->image = JSON[0][7].GetString();    //printData();
    this->title = JSON[0][8].GetString();    //printData();
    //JSON[0][8] is ornaments
    this->timestamp = JSON[0][13].GetUint64(); //   printData();
    if (JSON->Size() > 14) {
        for (int i = 0; i < 4; i++) {
            mods[i].owner   = JSON[0][14][i][0].GetString();
            mods[i].name    = JSON[0][14][i][1].GetString();
            mods[i].rarity  = JSON[0][14][i][2].GetString();
            // if(JSON[0][14][3].HasMember("REMOVAL_STICKINESS"))
            // mods[i].stats.removal_stickiness=JSON[0][14][3]["REMOVAL_STICKINESS"].GetUint();
        }
    }
    printData();
    return true;
}




void portal::printData() {
    std::cout << std::endl <<
              // raw << std::endl << std::endl <<
              "Team:          " << team << std::endl <<
              "latE6:         " << latE6 << std::endl <<
              "lngE6:         " << lngE6 << std::endl <<
              "Level:         " << level << std::endl <<
              "Health:        " << health << std::endl <<
              "Resonators:    " << resCount << std::endl <<
              "Image link:    " << image << std::endl <<
              "Title:         " << title << std::endl <<
              "Timestamp:     " << timestamp << std::endl;
    for (int i = 0; i < 4; i++) {
        std::cout << "Mod in slot " << i + 1 << ":" << std::endl;
        if (mods[i].name == "") {
            std::cout << "\tNot installed" << std::endl;
            continue;
        }
        std::cout << "\tName:   " << mods[i].name << std::endl <<
                  "\tRarity: " << mods[i].rarity << std::endl <<
                  "\tOwner:  " << mods[i].owner << std::endl;
    }
}