#pragma once
#include <iostream>
#include <cpr/cpr.h>
#include <cmath>
#include <time.h> //gmt to utc time.
#include <fstream>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"

class iitc
{
public:
    iitc(std::string settingsFileName);
    ~iitc();
    rapidjson::Document request(std::string method, std::string params);
    void setCookieSACSID(std::string SACSID);
    void setCSRF(std::string header);
    void login();
    time_t GMTtoUNIX(std::string time);
    rapidjson::Document parceJSONFromFile(std::string fileName);

private:
    std::string cookieSACSID;
    std::string cookieCSRF;
    std::string headerCSRF;
    std::string iitcBaseURL     = "https://www.ingress.com/r/";

    float one = 1.0f;
    float pi = 4 * atan(one);
public:
    int TILES_PER_EDGE[16] = {1, 1, 1, 40, 40, 80, 80, 320, 1000, 2000, 2000, 4000, 8000, 16000, 16000, 32000};
    long long lngToTile(long long lng, int tilesPerEdge);
    long long latToTile(long long lat, int tilesPerEdge);
    long long tileToLng(long long xTile, int tilesPerEdge);
    long long tileToLat(long long yTile, int tilesPerEdge);
    std::string pointToTileId(long long x, long long y, int zoom, short level);
};
