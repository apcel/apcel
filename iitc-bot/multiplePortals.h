#include <iostream>
#include <vector>
#include <algorithm>

#include "portal.h"
#include "iitc.h"
#include "rapidjson/document.h"
// #include ""
class multiplePortals
{


//pointinpolygon
//(c) http://alienryderflex.com/polygon/
//(c) Patrick Mullen
//  int    polyCorners  =  how many corners the polygon has (no repeats)
//  float  polyX[]      =  horizontal coordinates of corners
//  float  polyY[]      =  vertical coordinates of corners
//  float  x, y         =  point to be tested
    struct portalsInPolygon
    {
        int    polyCorners = 0;
        std::vector < double        >       polyX;
        std::vector < double        >       polyY;
        std::vector < std::string   >       tiles;
        std::vector < portal *      >       portals;
        std::vector < double        >       constant;
        std::vector < double        >       multiple;
    };
    // double x, y;

    std::vector < portalsInPolygon * > pocessedPolygons;
    std::string jsonSettingsFile = "secure/jsonSettingsFile.json";
    void precalc_values(portalsInPolygon * polygon);
    bool pointInPolygon(portalsInPolygon * polygon, double x, double y);
    int portalsWithLevel[9][2] = {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};
public:
    std::vector < portal  *          > gotPortals;
    // multiplePortals();
    // ~multiplePortals();

    //Useful for district stats
    bool acceptGEOJSON(std::string geoJSONString);

    //Select & paste
    bool acceptIITCPolygon(std::string copyPolygons);
    void process();
    void highestLevel(int numberOfSuch);
    void atLevel(short level);
    void wtf();




    struct greater
    {
        template<class T>
        bool operator()(T const &a, T const &b) const { return a > b; }
    };
    struct less
    {
        template<class T>
        bool operator()(T const &a, T const &b) const { return a < b; }
    };
};