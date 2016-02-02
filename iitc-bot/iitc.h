#pragma once
#include <iostream>
#include <cpr/cpr.h>
#include <cmath>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"

class iitc
{
public:
    iitc(std::string SACSID, std::string cookieCSRF);
    ~iitc();
    rapidjson::Document request(std::string method, std::string params);
    void setCookieSACSID(std::string SACSID);
    void setCSRF(std::string header);
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
/*
  var DEFAULT_ZOOM_TO_TILES_PER_EDGE = [1,1,1,40,40,80,80,320,1000,2000,2000,4000,8000,16000,16000,32000];
  var DEFAULT_ZOOM_TO_LEVEL = [8,8,8,8,7,7,7,6,6,5,4,4,3,2,2,1,1];

  // stock intel doesn't have this array (they use a switch statement instead), but this is far neater
  var DEFAULT_ZOOM_TO_LINK_LENGTH = [200000,200000,200000,200000,200000,60000,60000,10000,5000,2500,2500,800,300,0,0];
*/
/*
window.lngToTile = function(lng, params) {
    return Math.floor((lng + 180) / 360 * params.tilesPerEdge);
}

window.latToTile = function(lat, params) {
    return Math.floor((1 - Math.log(Math.tan(lat * Math.PI / 180) +
      1 / Math.cos(lat * Math.PI / 180)) / Math.PI) / 2 * params.tilesPerEdge);
}

window.tileToLng = function(x, params) {
    return x / params.tilesPerEdge * 360 - 180;
}

window.tileToLat = function(y, params) {
    var n = Math.PI - 2 * Math.PI * y / params.tilesPerEdge;
    return 180 / Math.PI * Math.atan(0.5 * (Math.exp(n) - Math.exp(-n)));
}

window.pointToTileId = function(params, x, y) {
    //change to quadkey construction
    //as of 2014-05-06: zoom_x_y_minlvl_maxlvl_maxhealth

    return params.zoom + "_" + x + "_" + y + "_" + params.level + "_8_100";
}
*/
/*
window.getMapZoomTileParameters = function(zoom) {
 // the current API allows the client to request a minimum portal level. the window.TILE_PARAMS.ZOOM_TO_LEVEL list are minimums
  // however, in my view, this can return excessive numbers of portals in many cases. let's try an optional reduction
  // of detail level at some zoom levels

  var level = window.TILE_PARAMS.ZOOM_TO_LEVEL[zoom] || 0;  // default to level 0 (all portals) if not in array
  var maxTilesPerEdge = window.TILE_PARAMS.TILES_PER_EDGE[window.TILE_PARAMS.TILES_PER_EDGE.length-1];

  return {
    level: level,
    maxLevel: window.TILE_PARAMS.ZOOM_TO_LEVEL[zoom] || 0,  // for reference, for log purposes, etc
    tilesPerEdge: window.TILE_PARAMS.TILES_PER_EDGE[zoom] || maxTilesPerEdge,
    minLinkLength: window.TILE_PARAMS.ZOOM_TO_LINK_LENGTH[zoom] || 0,
    hasPortals: zoom >= window.TILE_PARAMS.ZOOM_TO_LINK_LENGTH.length,  // no portals returned at all when link length limits things
    zoom: zoom  // include the zoom level, for reference
  };
}


*/