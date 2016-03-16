#pragma once
#include "iitc.h"

iitc::iitc(std::string gotSettingsFileName): settingsFileName(gotSettingsFileName) {
    // this->settingsFileName = gotSettingsFileName;
    settings = parceJSONFromFile(settingsFileName);

    if (cookiesExpired())
        reLogin();

    setCookieSACSID(settings["cookieSACSID"].GetString());
    setCSRF(settings["CSRF"].GetString());
}
iitc::~iitc() {

}
bool iitc::cookiesExpired() {
    settings = parceJSONFromFile(settingsFileName);
    // iitc iitc(settings["cookieSACSID"].GetString(),  settings["CSRF"].GetString(), settings["expires"].GetString());

    if ( true //for identation
            && settings.HasMember("cookieSACSID")
            && settings.HasMember("CSRF")
            && settings.HasMember("expires")
            && (GMTtoUNIX(settings["expires"].GetString()) - 100 > std::time(0))
       ) {
        //they are valid
        return false;
    }
    return true;
}
void iitc::reLogin() {
    system("phantomjs phantomjs.js");
    settings = parceJSONFromFile(settingsFileName);
    assert(settings.HasMember("expires"));
    assert(settings.HasMember("cookieSACSID"));
    assert(settings.HasMember("CSRF"));

    setCookieSACSID(settings["cookieSACSID"].GetString());
    setCSRF(settings["CSRF"].GetString());
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
    if (cookiesExpired())
        reLogin();

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
                        url//,
                        // cpr::Timeout{1000}
                    );
    rapidjson::Document jsonResponse;
    jsonResponse.Parse(response.text.c_str());
    if (jsonResponse.HasParseError()) {
        std::cerr << "Error with parsing server response [iitc.cpp ~86 line]. See yourself:" << std::endl;
        std::cerr << response.text << std::endl;
        if (retried)
            exit(2);
        retried = true;

        reLogin();
        return request(method, params);
        // std::cerr << "Request parms were: " << std::endl;
        // std::cerr << response.url << std::endl;
        // std::cerr << response.cookies.GetEncoded() << std::endl;

    };
    retried = false;
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


    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    params.Accept(writer);
    // std::cout << buffer.GetString();
    return buffer.GetString();
    // return "{\"tileKeys\":[\"15_19358_9999_0_8_100\",\"15_19360_9999_0_8_100\",\"15_19357_10003_0_8_100\",\"15_19357_10002_0_8_100\",\"15_19357_10001_0_8_100\"],\"v\":\"e5c8023daa723ce23479a6671c34b5c8112f9cb7\"}";
};

void iitc::shrink(std::vector<std::string> *from, std::vector<std::string> *to) {
    if (from->size() < toShrink)
        toShrink = from->size();
    // std::cout << from->size() << std::endl;
    for (int i = 0; i < toShrink; i++) {
        // std::cout << from->back() << "\n";
        to->push_back(from->back());
        // std::cout << to->back() << "\n";

        from->pop_back();
        // std::cout << to->back() << "\n";

    }

};


std::vector<portal*> iitc::fetchPortals(std::vector<std::string> tiles) {
    portal debugger;
    std::vector<portal*> portalsFromTiles;
//reorganize
    // std::vector<std::string> tiles;



// std::cout << "here";
    tilesToRetry.clear();
    for (int i = 0; i < 3; ++i)
    {

        int retries = 0;
        while ( false
                || (
                    ( !tilesToRetry.empty() )
                    && (retries < 5)
                )
                || retries < 1
              )
        {
            if (tiles.empty())
                retries++;
            usleep(1e5 * 1); //one millisecond

            ///////////////

            std::vector<std::string> finalParms;

            std::string symbol;
            std::string params;
            if (!tiles.empty()) {
                shrink(&tiles, &finalParms);
                symbol = ".";
            } else {
                shrink(&tilesToRetry, &finalParms);
                usleep(1e6); //one second
                symbol = "'";
            }
            if (finalParms.empty())
                continue;

            params = constructRequest(finalParms, this->version_constant);
            // std::cout << params << "\n";
            rapidjson::Document area = request("getEntities", params);

            ////////////////



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


            bool saved = false;
            rapidjson::Value & map = area["result"]["map"];
            for (
                rapidjson::Value::MemberIterator responsedTile = map.MemberBegin();
                responsedTile != map.MemberEnd();
                responsedTile++
            ) {
                rapidjson::Value & tileFromResponse = responsedTile->value;
                std::string tileName = responsedTile->name.GetString();
                if (false
                        || (!tileFromResponse.IsObject())
                        || (
                            (
                                (!tileFromResponse.HasMember("gameEntities"))
                                || (!tileFromResponse["gameEntities"].IsArray())
                            )
                            && tileFromResponse.HasMember("error")
                        )
                   ) {
                    if (!saved) {
                        // logger.open("log", "app");
                        logger.open("log", std::fstream::app | std::fstream::out);

                        logger << std::endl << "/*//////////////////////////*/" << std::endl;
                        rapidjson::StringBuffer buffer;
                        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
                        area.Accept(writer);
                        logger << buffer.GetString() << std::endl;
                        logger.close();
                        saved = true;
                    }
                    // std::cerr << "error while parsing " + tileName + " tile data! gonna try later..\n";
                    debugger.debugJsonErr(&tileFromResponse);
                    if (tileFromResponse.HasMember("error")) {
                        tilesToRetry.push_back(tileName);
                        if (!strcasecmp(tileFromResponse["error"].GetString(), "error"))
                            std::cerr << tileFromResponse["error"].GetString() << "\n";
                        std::cerr << "e";
                    } else {
                        std::cerr << "N";
                    }

                    continue;
                } else {
                    std::cerr << symbol;
                    // tilesToRetry.delete
                    // debugger.debugJsonErr(&tileFromResponse);
                    // std::cerr << "Tile " + tileName + " done successfully" << std::endl;
                    tilesToRetry.erase(std::remove(tilesToRetry.begin(), tilesToRetry.end(), tileName), tilesToRetry.end());
                }
                for (
                    rapidjson::SizeType numberOfEntity = 0;
                    numberOfEntity < tileFromResponse["gameEntities"].Size();
                    numberOfEntity++
                ) {
                    std::string type = tileFromResponse["gameEntities"][numberOfEntity][2][0].GetString();

                    portal * tempPortal = new portal();
                    if (!strcmp(type.c_str(), "p")) //is portal
                    {
                        // debugger.debugJsonErr(&tileFromResponse["gameEntities"][numberOfEntity]);
                        // portal tempPortal;
                        tempPortal->updateWith(tileFromResponse["gameEntities"][numberOfEntity]);
                        portalsFromTiles.push_back(tempPortal);
                        // portalsFromTiles.back()->printData();
                    } else {
                        delete tempPortal;
                    }
                    // std::cerr << "not a portal\n";
                };
            };
        }
        if (!tilesToRetry.empty()) {
            std::cerr << "could not fetch all tiles\n";
            std::sort(tilesToRetry.begin(), tilesToRetry.end());
            usleep(1e5); //0.1 second
        }
    }
    if (!tilesToRetry.empty())
        std::cout << "Warning! Could not fetch all data\n";
    // for (auto i : portalsFromTiles)
    //     i->printData();
    return portalsFromTiles;
}
























