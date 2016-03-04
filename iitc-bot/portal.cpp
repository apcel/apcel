#pragma once
#include "portal.h"
portal::portal( rapidjson::Value& parent) {
// debugJsonErr(&parent);
    json = portalDetail(parent);

};
portal::~portal() {};
portal::portal() {};

void portal::debugJsonErr(rapidjson::Value * JSON) {
// #ifdef DEBUG
    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    JSON->Accept(writer);
    std::cerr << "For debugging purposes, printing serialized input json:" << std::endl <<
              buffer.GetString() << std::endl;
// #endif
};
void portal::updateWith(rapidjson::Value JSON) {

// // reset();
// /*..and save raw portal data*/
// rapidjson::StringBuffer buffer;
// rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
// JSON->Accept(writer);
// raw = buffer.GetString();
// if (JSON->IsObject()) {
// assert(JSON[0].HasMember("result"));
// return parseArray(&JSON[0]["result"]);
// } else {
// return parseArray(&JSON[0][2]);
// }
// return false;
};

/*bool portal::parseArray(rapidjson::Value * JSON) {
 if (!JSON[0][0].IsString())
 debugJsonErr(&JSON[0]);
 if (std::strncmp(JSON[0][0].GetString(), "p", 1))
 // return false;
 // this->team = JSON[0][1].GetString(); // printData();
 // this->latE6 = JSON[0][2].GetInt(); // printData();
 // this->lngE6 = JSON[0][3].GetUint64(); // printData();
 // this->level = JSON[0][4].GetInt(); //printData();
 // this->health = JSON[0][5].GetDouble(); // printData();
 // this->resCount = JSON[0][6].GetInt(); //printData();
 // this->image = JSON[0][7].GetString(); //printData();
 // this->title = JSON[0][8].GetString(); //printData();
 // //JSON[0][8] is ornaments
 // this->timestamp = JSON[0][13].GetUint64(); // printData();
 if (JSON->Size() > 14) {
 fullInfo = true;
 rapidjson::Value & modsJSON = JSON[0][14];
 for (int i = 0; i < 4; i++) {
 rapidjson::Value & mod = modsJSON[i];
 // mods[i].owner = mod[0].GetString();
 // mods[i].name = mod[1].GetString();
 // mods[i].rarity = mod[2].GetString();
 // if(JSON[0][14][3].HasMember("REMOVAL_STICKINESS"))
 // mods[i].stats.removal_stickiness=JSON[0][14][3]["REMOVAL_STICKINESS"].GetUint();
 }
 rapidjson::Value & resonatorsJSON = JSON[0][15];
 for (int i = 0; i < 8; i++) {
 rapidjson::Value & resonatorJSON = resonatorsJSON[i];
 if (resonatorJSON[1].GetInt() == 0)
 continue;
 // resonators[i].owner = resonatorJSON[0].GetString();
 // resonators[i].level = resonatorJSON[1].GetInt();
 // resonators[i].energy = resonatorJSON[2].GetInt();

 //Collect total resonators level. Can be used for alarms, for example
 // resonatorsLevelSum += resonators[i].level;
 }
 }
 // printData();
 return true;
}
*/



void portal::printData() {
    char writeBuffer[65536];
    rapidjson::FileWriteStream os(stdout, writeBuffer, sizeof(writeBuffer));
    rapidjson::PrettyWriter<rapidjson::FileWriteStream> writer(os);

    std::cout << std::endl;
    json.Accept(writer);
    std::cout << std::endl;
}



rapidjson::Document portal::parseResonator(rapidjson::Value &arr) {
    rapidjson::Document resonator(rapidjson::kObjectType);
    if (arr.IsNull()) {
        resonator.SetNull();
    } else {
        resonator.AddMember("owner", arr[0], json.GetAllocator());
        resonator.AddMember("level", arr[1], json.GetAllocator());
        resonator.AddMember("energy", arr[2], json.GetAllocator());
    }
    return resonator;
};
rapidjson::Document portal::parseMod(rapidjson::Value &arr) {
    rapidjson::Document mod(rapidjson::kObjectType);
    if (arr.IsNull()) {
        mod.SetNull();
    } else {
        mod.AddMember("owner", arr[0], json.GetAllocator());
        mod.AddMember("name", arr[1], json.GetAllocator());
        mod.AddMember("rarity", arr[2], json.GetAllocator());
        mod.AddMember("stats", arr[3], json.GetAllocator());
    };
    return mod;
};
rapidjson::Document portal::corePortalData(rapidjson::Value &arr) {
    rapidjson::Document core(rapidjson::kObjectType);
    core.AddMember("team", arr[1], json.GetAllocator());
    core.AddMember("latE6", arr[2], json.GetAllocator());
    core.AddMember("lngE6", arr[3], json.GetAllocator());
    return core;
};

rapidjson::Document portal::summaryPortalData(rapidjson::Value &arr) {
    rapidjson::Document summary;
    summary = corePortalData(arr);
    summary.AddMember("level", arr[4], json.GetAllocator());
    summary.AddMember("health", arr[5], json.GetAllocator());
    summary.AddMember("resCount", arr[6], json.GetAllocator());
    summary.AddMember("image", arr[7], json.GetAllocator());
    summary.AddMember("title", arr[8], json.GetAllocator());
    summary.AddMember("ornaments", arr[9], json.GetAllocator());
    summary.AddMember("mission", arr[10], json.GetAllocator());
    summary.AddMember("mission50plus", arr[11], json.GetAllocator());
    summary.AddMember("timestamp", arr[13], json.GetAllocator());

    return summary;
};

rapidjson::Document portal::portalDetail(rapidjson::Value &fullArr) {
    rapidjson::Document details(rapidjson::kObjectType);
    if ( !strncmp(fullArr[0].GetString(), "p", 1) ) {
        std::cerr << "Not a portal!" << std::endl;
        debugJsonErr(&fullArr);
        return details;
    };
    rapidjson::Value & arr = fullArr[2];
    assert(arr.Size() <= 18);
    // std::cerr << "Here [asserted]\n";
    details = summaryPortalData(arr);
    details.AddMember("id", fullArr[0], json.GetAllocator());
    details.AddMember("timestamp", fullArr[1], json.GetAllocator());
    // std::cerr << "Here [summary got]\n";
    // std::cerr << "Size: " << arr.Size() << "\n";

    if (arr.Size() > 14) {
        rapidjson::Value mods(rapidjson::kArrayType);
        rapidjson::Value resonators(rapidjson::kArrayType);
        for (int itera = 0; itera < 4; itera++)
            mods.PushBack(parseMod(arr[14][itera]), json.GetAllocator());
        for (int itera = 0; itera < 8; itera++)
            resonators.PushBack(parseResonator(arr[15][itera]), json.GetAllocator());

        details.AddMember("mods", mods, json.GetAllocator());
        details.AddMember("resonators", resonators, json.GetAllocator());
        details.AddMember("owner", arr[16], json.GetAllocator());
    };
    return details;
};


bool portal::operator < ( portal& that)
{
    if (this->hasFullInfo() && that.hasFullInfo())
        return (this->getResCount() < that.getResCount());
    else
        return (this->getLevel() < that.getLevel());
}

 bool portal::hasFullInfo() {
    return fullInfo;
}

 std::string portal::getTeam() {
    if (!json.HasMember("team")) {
        std::cerr << "Error while getting " << "team" << std::endl;
        return "";
    }
    return json["team"].GetString();
}
 int portal::getLatE6() {
    if (!json.HasMember("latE6")) {
        std::cerr << "Error while getting " << "latE6" << std::endl;
        return 0;
    }
    return json["latE6"].GetInt();
}
 long portal::getLngE6() {
    if (!json.HasMember("lngE6")) {
        std::cerr << "Error while getting " << "lngE6" << std::endl;
        return 0;
    }
    return json["lngE6"].GetUint64();
}
 int portal::getLevel() {
    if (!json.HasMember("level")) {
        std::cerr << "Error while getting " << "level" << std::endl;
        return 0;
    }
    return json["level"].GetInt();
}
 double portal::getHealth() {
    if (!json.HasMember("health")) {
        std::cerr << "Error while getting " << "health" << std::endl;
        return 0;
    }
    return json["health"].GetDouble();
}
 int portal::getResCount() {
    if (!json.HasMember("resCount")) {
        std::cerr << "Error while getting " << "resCount" << std::endl;
        return 0;
    }
    return json["resCount"].GetInt();
}
 std::string portal::getImage() {
    if (!json.HasMember("image")) {
        std::cerr << "Error while getting " << "image" << std::endl;
        return "";
    }
    return json["image"].GetString();
}
 std::string portal::getTitle() {
    if (!json.HasMember("title")) {
        std::cerr << "Error while getting " << "title" << std::endl;
        return "";
    }
    return json["title"].GetString();
}
 short portal::getResSum() {
    return resonatorsLevelSum;
}
