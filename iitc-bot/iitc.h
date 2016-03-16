#pragma once
#include <iostream>
#include <cpr/cpr.h>
#include <cmath>
#include <time.h> //gmt to utc time.
#include <fstream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <unistd.h> // sleep


#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "portal.h"

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
    rapidjson::Document settings;
    std::string settingsFileName;
    bool cookiesExpired();
    void reLogin();
    bool retried = false;

    std::fstream logger;

    std::vector<std::string> tilesToRetry;
    std::string cookieSACSID;
    std::string cookieCSRF;
    std::string headerCSRF;
    std::string iitcBaseURL     = "https://www.ingress.com/r/";

    float one = 1.0f;
    float pi = 4 * atan(one);

    std::string version_constant = "d631d3024d7cd07f18c65b93f40a4d592d0ea7a5";
    std::string constructRequest(std::vector<std::string> tileKeys, std::string version);

    std::vector<std::string> tempString;

    short toShrink = 4;
    void shrink(std::vector<std::string> *from, std::vector<std::string> *to);
public:
    int TILES_PER_EDGE[16] = {1, 1, 1, 40, 40, 80, 80, 320, 1000, 2000, 2000, 4000, 8000, 16000, 16000, 32000};
    long long lngToTile(long long lng, int tilesPerEdge);
    long long latToTile(long long lat, int tilesPerEdge);
    long long tileToLng(long long xTile, int tilesPerEdge);
    long long tileToLat(long long yTile, int tilesPerEdge);
    std::string pointToTileId(long long x, long long y, int zoom, short level);

    std::vector<portal*> fetchPortals(std::vector<std::string> tiles);
};
