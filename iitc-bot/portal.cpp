#pragma once
#include "portal.h"
portal::portal() {reset();};
portal::~portal() {};
void portal::reset() {
    uid = "";
    team = "";
    latE6 = 0;
    lngE6 = 0;
    level = 0;
    health = 0;
    resCount = 0;
    image = "";
    title = "";
    timestamp = 0;

    // modInfo mods[4];
    for (int i = 0; i < 4; i++) {
        mods[i].name = "";
        mods[i].owner = "";
        mods[i].rarity = "";
    }
    resonator resonators[8];
    owner = "";
    resonatorsLevelSum = 0;

    raw = "";

};

void portal::debugJsonErr(rapidjson::Value * JSON) {
#ifdef DEBUG
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    JSON->Accept(writer);
    std::cerr << "For debugging purposes, printing serialized input json:" << std::endl <<
              buffer.GetString() << std::endl;
#endif
};

bool portal::parseJSON(rapidjson::Value * JSON) {
    reset();
    /*..and save raw portal data*/
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    JSON->Accept(writer);
    raw = buffer.GetString();
    if (JSON->IsObject()) {
        assert(JSON[0].HasMember("result"));
        return parseArray(&JSON[0]["result"]);
    } else {
        return parseArray(&JSON[0][2]);
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
        fullInfo = true;
        rapidjson::Value & modsJSON = JSON[0][14];
        for (int i = 0; i < 4; i++) {
            rapidjson::Value & mod = modsJSON[i];
            mods[i].owner   = mod[0].GetString();
            mods[i].name    = mod[1].GetString();
            mods[i].rarity  = mod[2].GetString();
            // if(JSON[0][14][3].HasMember("REMOVAL_STICKINESS"))
            // mods[i].stats.removal_stickiness=JSON[0][14][3]["REMOVAL_STICKINESS"].GetUint();
        }
        rapidjson::Value & resonatorsJSON = JSON[0][15];
        for (int i = 0; i < 8; i++) {
            rapidjson::Value & resonatorJSON = resonatorsJSON[i];
            if (resonatorJSON[1].GetInt() == 0)
                continue;
            resonators[i].owner = resonatorJSON[0].GetString();
            resonators[i].level = resonatorJSON[1].GetInt();
            resonators[i].energy = resonatorJSON[2].GetInt();

            //Collect total resonators level. Can be used for alarms, for example
            resonatorsLevelSum += resonators[i].level;
        }
    }
    // printData();
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

    if (fullInfo) {
        std::cout << "Mods:" << std::endl;
        for (int i = 0; i < 4; i++) {
            std::cout << "\tMod in slot " << i + 1 << ":" << std::endl;
            if (mods[i].name == "") {
                std::cout << "\t\tNot installed" << std::endl;
                continue;
            }
            std::cout << "\t\tName:   " << mods[i].name << std::endl <<
                      "\t\tRarity: " << mods[i].rarity << std::endl <<
                      "\t\tOwner:  " << mods[i].owner << std::endl;
        }
        if (resonatorsLevelSum > 0) {
            std::cout << "Resonators: " << std::endl;
            for (int i = 0; i < 8; i++) {
                std::cout << "\tResonator " << i << ":" << std::endl <<
                          "\t\tLevel :  " << resonators[i].level <<  std::endl <<
                          "\t\tOwner :  " << resonators[i].owner << std::endl <<
                          "\t\tCharge:  " << resonators[i].energy << std::endl;
            }
            /* code */
        }
    }
}