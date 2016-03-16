#pragma once
#include "portal.h"
portal::portal( rapidjson::Value& parent) {
// debugJsonErr(&parent);
    this->json = portalDetail(parent);

};
portal::~portal() {};
portal::portal() {};
portal::portal(const portal * parent) {
    this->json.CopyFrom(parent->json, this->json.GetAllocator());
    this->fullInfo = parent->fullInfo;
    this->resonatorsLevelSum = parent->resonatorsLevelSum;
};

portal::portal(const portal& parent) {
    this->json.CopyFrom(parent.json, this->json.GetAllocator());
    this->fullInfo = parent.fullInfo;
    this->resonatorsLevelSum = parent.resonatorsLevelSum;
}

void portal::debugJsonErr(rapidjson::Value * JSON) {
// #ifdef DEBUG
    return;
    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    JSON->Accept(writer);
    std::cerr << "For debugging purposes, printing serialized input json:" << std::endl <<
              buffer.GetString() << std::endl;
// #endif
};
void portal::updateWith(rapidjson::Value & JSON) {
    this->json.CopyFrom(portalDetail(JSON), this->json.GetAllocator());
};




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
    if (!strcasecmp(summary["team"].GetString(), "N"))
        summary.AddMember("level", 0, json.GetAllocator());
    else
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
bool portal::operator > ( portal& that)
{
    if (this->hasFullInfo() && that.hasFullInfo())
        return (this->getResCount() > that.getResCount());
    else
        return (this->getLevel() > that.getLevel());
}


void portal::operator = ( portal& that)
{
    this->json.CopyFrom(that.json, this->json.GetAllocator());
    this->fullInfo = that.fullInfo;
    this->resonatorsLevelSum = that.resonatorsLevelSum;
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
long portal::getLatE6() {
    if (!json.HasMember("latE6")) {
        std::cerr << "Error while getting " << "latE6" << std::endl;
        return 0;
    }
    return json["latE6"].GetUint64();
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
