#pragma once
#include "iitc.h"

iitc::iitc(std::string SACSID, std::string cookieCSRF) {
    setCookieSACSID(SACSID);
    setCSRF(cookieCSRF);
}
iitc::~iitc() {

}


rapidjson::Document iitc::request(std::string method, std::string params) {

    auto cookies =  cpr::Cookies
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
    auto url =                         cpr::Url
    {
        iitcBaseURL + method
    };
    auto response = cpr::Post(
                        cookies,
                        headers,
                        body,
                        url
                    );

    // std::cout << response.text << std::endl << std::endl;


    rapidjson::Document jsonResponse;
    jsonResponse.Parse(response.text.c_str());
    if (jsonResponse.HasParseError()) {
        // std::cerr << response.
        auto another_r = cpr::Get(cpr::Url{"http://www.httpbin.org/cookies"}, cookies);
        std::cout << another_r.text << std::endl;
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
    // assert(!cookie.empty());
    // assert(!header.empty());
    // headerCSRF = header;
    cookieCSRF = CSRF;
};

long long iitc::lngToTile(long long lng1, int tilesPerEdge) {
    float lng = static_cast<float>(lng1) / 1000000;
    // std::cout << tilesPerEdge << " " << lng << " " << 3.1415926f << std::endl;
    float value = tilesPerEdge * (lng + 180) / 360;
    return floorf(value);
};
long long iitc::latToTile(long long lat1, int tilesPerEdge) {
    float lat = static_cast<float>(lat1) / 1000000;
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
/*
window.lngToTile = function(lng, params) {
    return floor((lng + 180) / 360 * params.tilesPerEdge);
}

window.latToTile = function(lat, params) {
    return floor((1 - log(tan(lat * pi / 180) +
      1 / cos(lat * pi / 180)) / pi) / 2 * params.tilesPerEdge);
}

window.tileToLng = function(x, params) {
    return x / params.tilesPerEdge * 360 - 180;
}

window.tileToLat = function(y, params) {
    var n = pi - 2 * pi * y / params.tilesPerEdge;
    return 180 / pi * atan(0.5 * (exp(n) - exp(-n)));
}

window.pointToTileId = function(params, x, y) {
    //change to quadkey construction
    //as of 2014-05-06: zoom_x_y_minlvl_maxlvl_maxhealth

    return params.zoom + "_" + x + "_" + y + "_" + params.level + "_8_100";
}*/