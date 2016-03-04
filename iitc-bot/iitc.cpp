#pragma once
#include "iitc.h"

iitc::iitc(std::string settingsFileName) {
    rapidjson::Document settings = parceJSONFromFile(settingsFileName);
    // iitc iitc(settings["cookieSACSID"].GetString(),  settings["CSRF"].GetString(), settings["expires"].GetString());

    if (
        !settings.HasMember("cookieSACSID") ||
        !settings.HasMember("CSRF") ||
        !settings.HasMember("expires") ||
        GMTtoUNIX(settings["expires"].GetString()) - 100 < std::time(0)
    ) {
        system("phantomjs phantomjs.js");
        settings = parceJSONFromFile(settingsFileName);
        assert(settings.HasMember("expires"));
        assert(settings.HasMember("cookieSACSID"));
        assert(settings.HasMember("CSRF"));
    }

    setCookieSACSID(settings["cookieSACSID"].GetString());
    setCSRF(settings["CSRF"].GetString());
}
iitc::~iitc() {

}
rapidjson::Document iitc::parceJSONFromFile(std::string fileName) {
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

rapidjson::Document iitc::request(std::string method, std::string params) {

    auto cookies = cpr::Cookies
    {
        {
            "SACSID", cookieSACSID
        },

        {
            "csrftoken", cookieCSRF
        }
    };
    auto headers = cpr::Header
    {

        {
            "Accept", "application/json"
        },
        {
            "Referer", "https://www.ingress.com/intel"
        },
        {
            "X-CSRFToken", cookieCSRF
        },
        {
            "X-Requested-With", "XMLHttpRequest"
        }
    };
    auto body = cpr::Body
    {
        params
    };
    auto url = cpr::Url
    {
        iitcBaseURL + method
    };
    auto response = cpr::Post(
                        cookies,
                        headers,
                        body,
                        url
                    );
    rapidjson::Document jsonResponse;
    jsonResponse.Parse(response.text.c_str());
    if (jsonResponse.HasParseError()) {
        std::cerr << "Error with parsing server response [iitc.cpp ~86 line]. See yourself:" << std::endl;
        std::cerr << response.text << std::endl;
        exit(2);
    };
    return jsonResponse;

}

void iitc::setCookieSACSID(std::string SACSID) {
    assert(!SACSID.empty());
    cookieSACSID = SACSID;
};
void iitc::setCSRF(std::string CSRF) {
    assert(!CSRF.empty());
    cookieCSRF = CSRF;
};

long long iitc::lngToTile(long long lng1, int tilesPerEdge) {
    float lng = static_cast<float>(lng1) / 1e6; //portals have lngE6 coords
    float value = tilesPerEdge * (lng + 180) / 360;
    return floorf(value);
};
long long iitc::latToTile(long long lat1, int tilesPerEdge) {
    float lat = static_cast<float>(lat1) / 1e6; //portals have latE6 coords
    float sina = sin(lat * pi / 180);
    float cosa = cos(lat * pi / 180);
    float loga = log((sina + 1) / cosa);
    float value =  tilesPerEdge * (1 - loga / pi) / 2;
    return floorf(value);
};
long long iitc::tileToLng(long long xTile, int tilesPerEdge) {
    return xTile / tilesPerEdge * 360 - 180;
};
long long iitc::tileToLat(long long yTile, int tilesPerEdge) {
    float n = pi - 2 * pi * yTile / tilesPerEdge;
    return 180 / pi * atan(0.5 * (exp(n) - exp(-n)));
};
std::string iitc::pointToTileId(long long x, long long y, int zoom, short level) {
    return std::to_string(zoom) + "_" + std::to_string(x) + "_" + std::to_string(y) + "_" + std::to_string(level) + "_8_100";
};

time_t iitc::GMTtoUNIX(std::string time) {
    struct tm tm;
    char buf[255];
    memset(&tm, 0, sizeof(struct tm));
    time_t expiration;
    strptime(time.c_str(), "%a, %d %b %Y %T GMT", &tm);
    strftime(buf, sizeof(buf), "%s" , &tm);
    expiration = atoi(buf);
    return expiration;
}

std::string iitc::constructRequest(std::vector<std::string> tileKeys, std::string version) {
    rapidjson::Document params;
    params.SetObject();

    rapidjson::StringBuffer buffer;
    buffer.Clear();

    // rapidjson::Document::AllocatorType & allocator = params.GetAllocator();
    rapidjson::Document::AllocatorType & allocator = params.GetAllocator();

    rapidjson::Value tileKeysArray;
    tileKeysArray.SetArray();
    for (auto key : tileKeys) {
        rapidjson::Value tmpString;
        tmpString.SetString(key.c_str(), allocator);
        // std::cout << tmpString.GetString() << std::endl;
        tileKeysArray.PushBack(tmpString, allocator);
    }
    params.AddMember("tileKeys", tileKeysArray, allocator);

    // buffer = version;
    rapidjson::Value tmpString;

    tmpString.SetString(version.c_str(), allocator);
    params.AddMember("v", tmpString, allocator);


    // std::string constructRequest(std::vector<std::string> tileKeys, std::string version);
    buffer.Clear();

    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    params.Accept(writer);

    // return buffer.GetString();
    return "{\"tileKeys\":[\"15_19358_9999_0_8_100\",\"15_19360_9999_0_8_100\",\"15_19357_10003_0_8_100\",\"15_19357_10002_0_8_100\",\"15_19357_10001_0_8_100\"],\"v\":\"e5c8023daa723ce23479a6671c34b5c8112f9cb7\"}";
};



std::vector<portal*> iitc::fetchPortals(std::vector<std::string> tiles) {
    portal debugger;
    tempString = tiles;
// std::cout << "here";

    std::vector<portal*> portalsFromTiles;
    std::string params = constructRequest(tempString, this->version_constant);
    rapidjson::Document area = request("getEntities", params);

    //get all portals
    if (false
            || (!area.IsObject())
            || (!area.HasMember("result"))
            || (!area["result"].IsObject())
            || (!area["result"].HasMember("map"))
            || (!area["result"]["map"].IsObject())
       ) {
        std::cerr << "error while getting data!\n";
        if (!area.IsObject())
            std::cerr << "(!area.IsObject())" << std::endl;
        else if (!area.HasMember("result"))
            std::cerr << "(!area.HasMember(\"result\"))" << std::endl;
        else if (!area["result"].IsObject())
            std::cerr << "(!area[\"result\"].IsObject())" << std::endl;
        else if (!area["result"].HasMember("map"))
            std::cerr << "(!area[\"result\"].HasMember(\"map\"))" << std::endl;
        else if (!area["result"]["map"].IsObject())
            std::cerr << "(!area[\"result\"][\"map\"].IsObject())" << std::endl;
        debugger.debugJsonErr(&area);

        exit(1);
    }


    rapidjson::Value & map = area["result"]["map"];
    for (
        rapidjson::Value::MemberIterator responsedTile = map.MemberBegin();
        responsedTile != map.MemberEnd();
        responsedTile++
    ) {
        rapidjson::Value & tileFromResponse = responsedTile->value;
        if (false
                || (!tileFromResponse.IsObject())
                || (!tileFromResponse.HasMember("gameEntities"))
                || (!tileFromResponse["gameEntities"].IsArray())
           ) {
            std::cerr << "error while parsing tile data! skipping..\n";
            continue;
        }
        for (
            rapidjson::SizeType numberOfEntity = 0;
            numberOfEntity < tileFromResponse["gameEntities"].Size();
            numberOfEntity++
        ) {
            std::string type = tileFromResponse["gameEntities"][numberOfEntity][2][0].GetString();

            if (!strcmp(type.c_str(), "p")) //is portal
            {
                debugger.debugJsonErr(&tileFromResponse["gameEntities"][numberOfEntity]);
                portal * tempPortal = new portal(tileFromResponse["gameEntities"][numberOfEntity]);
                portalsFromTiles.push_back(tempPortal);
            }
            // else
            // std::cerr << "not a portal\n";
        };
    };

    return portalsFromTiles;
}
























