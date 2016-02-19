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

    setCookieSACSID(settings["SACSID"].GetString());
    setCSRF(settings["cookieCSRF"].GetString());
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
        std::cerr << "Error with parsing server response. See yourself:" << std::endl;
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