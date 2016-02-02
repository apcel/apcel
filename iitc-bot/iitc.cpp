#pragma once
#include "iitc.h"

iitc::iitc(std::string SACSID, std::string headerCSRF, std::string cookieCSRF) {
    setCookieSACSID(SACSID);
    setCSRF(cookieCSRF, headerCSRF);
}
iitc::~iitc() {

}


rapidjson::Document iitc::request(std::string method, std::string params) {

    auto response = cpr::Post(
                        cpr::Url
    {
        iitcBaseURL + method
    },

    cpr::Header
    {
        {
            "Cookie", cookieSACSID + cookieCSRF
        },
        {
            "Accept", "application/json"
        },
        {
            "Referer", "https://www.ingress.com/intel"
        },
        {
            "X-CSRFToken", headerCSRF
        }
    },

    cpr::Body
    {
        "{\"guid\":\"fa0838e5401643b6ac6b58b981f3994f.16\",\"v\":\"9ffe0cfdf367c491a20802d3c606d679992e8b08\"}"
    }
                    );

    // std::cout << response.text << std::endl << std::endl;


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
void iitc::setCSRF(std::string cookie, std::string header) {
    assert(!cookie.empty());
    assert(!header.empty());
    headerCSRF = header;
    cookieCSRF = cookie;
};

long long iitc::lngToTile(long long lng, int tilesPerEdge) {
    return tilesPerEdge * (lng + 180) / 360;
};
long long iitc::latToTile(long long lat, int tilesPerEdge) {
    return  tilesPerEdge * (1 - log(tan(lat * pi / 180)
                    + 1 / cos(lat * pi / 180)) / pi) / 2;
};
long long iitc::tileToLng(long long xTile, int tilesPerEdge) {
    return xTile / tilesPerEdge * 360 - 180;
};
long long iitc::tileToLat(long long yTile, int tilesPerEdge) {
    double n = pi - 2 * pi * yTile / tilesPerEdge;
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