#include "multiplePortals.h"


bool multiplePortals::acceptGEOJSON(std::string geoJSONString) {
    // rapidjson::Document geoJSON;
    // geoJSON.Parse(geoJSONString.c_str());

    std::cerr << "Not implemented!" << std::endl;
    exit(1);
    return true;
}

bool multiplePortals::acceptIITCPolygon(std::string copyPolygons) {
    portal debugger;
    rapidjson::Document geoJSON;
    geoJSON.Parse(copyPolygons.c_str());
    //drawtools exports like this:
    /*
    array of objects
    Each object has "type" and "latlngs" fields
    "type" is string
    "LatLngs" is array of objects of points
    Each point is pair of float "lat" and "lng" fields
    */
    // debugger.debugJsonErr(&geoJSON);
    pocessedPolygons.clear();
    if (geoJSON.IsArray())
    {
        // cycle through polygons
        for (rapidjson::SizeType polygonNumber = 0;
                polygonNumber < geoJSON.Size(); polygonNumber++) {
            rapidjson::Value & polygonsArrayIterator = geoJSON[polygonNumber];
            // debugger.debugJsonErr(&polygonsArrayIterator);

            //skip non-polygons and not having latLngs array polygons
            if (    false/*for identation*/
                    ||  ( ! polygonsArrayIterator.IsObject()                                                    )
                    ||  ( ! polygonsArrayIterator.HasMember("type")                                             )
                    ||  ( ! polygonsArrayIterator["type"].IsString()                                            )
                    // ||  ( ! strncmp(polygonsArrayIterator["type"].GetString(), "polygon", 6)                    )
                    ||  ( ! polygonsArrayIterator.HasMember("latLngs")                                          )
               ) {
                std::cerr << "non-polygon\n" << polygonsArrayIterator["type"].GetString() << "\n";
                continue;
            }

            //cycle through array of latlngs objects
            const rapidjson::Value & latLngs = polygonsArrayIterator["latLngs"];

            portalsInPolygon * polygon = new portalsInPolygon;

            for (rapidjson::SizeType polygonPointNumber = 0;
                    polygonPointNumber < latLngs.Size(); polygonPointNumber++) {
                const rapidjson::Value & point = latLngs[polygonPointNumber];

                //skip invalid points
                if ( false/*for identation*/
                        || ( ! point.IsObject()         )
                        || ( ! point.HasMember("lat")   )
                        || ( ! point["lat"].IsDouble()  )
                        || ( ! point.HasMember("lng")   )
                        || ( ! point["lng"].IsDouble()  )
                   ) {
                    std::cerr << "invalid point\n";
                    continue;
                }
                //point is valid, save it's data
                polygon->polyX.push_back(point["lat"].GetDouble());
                polygon->polyY.push_back(point["lng"].GetDouble());
                polygon->polyCorners++;
                // std::cout << polygon->polyX.back() << "\t" << polygon->polyY.back() << "\t" << polygon->polyCorners << std::endl;
            } // cycle through array of latlngs objects
            if (polygon->polyCorners > 2) { //is valid
                //calculate points
                std::vector<long long> pointTilesX;
                std::vector<long long> pointTilesY;
                iitc intel("jsonSettingsFile.json");
                for (auto xPoint : polygon->polyX) {
                    pointTilesX.push_back(intel.latToTile(xPoint * 1e6, intel.TILES_PER_EDGE[15]));
                    // std::cout << pointTilesX.back() << std::endl;
                }
                for (auto yPoint : polygon->polyY)
                    pointTilesY.push_back(intel.lngToTile(yPoint * 1e6, intel.TILES_PER_EDGE[15]));
                std::sort(pointTilesX.begin(), pointTilesX.end());
                std::sort(pointTilesY.begin(), pointTilesY.end());

                for (long long i = pointTilesX.front(); i <= pointTilesX.back(); i++)
                    for (long long j = pointTilesY.front(); j <= pointTilesY.back(); j++)
                        polygon->tiles.push_back(intel.pointToTileId(i, j, 15, 0));
                // // print it
                // for (auto i : polygon->tiles)
                //     std::cout << i << std::endl;
                //and save
                this->pocessedPolygons.push_back(polygon);
            } else {
                delete polygon;
            }
        };// cycle through polygons
    } else {
        std::cerr << "Not an array!" << std::endl;
    }
    if (pocessedPolygons.empty())
        return false;
    else
        return true;
}

void multiplePortals::process() {
    iitc intel("jsonSettingsFile.json");
    for (auto polygon : pocessedPolygons) {
        std::vector < portal * > got = intel.fetchPortals(polygon->tiles);
        gotPortals.insert( gotPortals.end(), got.begin(), got.end() );
    }
    std::cout << "got " << gotPortals.size() << " portals\n";
}


void multiplePortals::highestLevel(int numberOfSuch) {
    std::sort(gotPortals.begin(), gotPortals.end());
    for (int i = gotPortals.size() - numberOfSuch; i < gotPortals.size() ; ++i)
    {
        gotPortals[i]->printData();
        // std::cout << "Title:" << gotPortals[i]->getTitle() << std::endl;
        // std::cout << "Level:" << gotPortals[i]->getLevel() << std::endl;
    }
};
void multiplePortals::atLevel(short level) {

    for (auto i : gotPortals)
    {
        if(i->getLevel() == level)
            i->printData();
    }
};
void multiplePortals::wtf() {
    bool isSomethingUnequal = false;
    for(auto i:gotPortals)
        for(auto j:gotPortals)
            if(i != j) {
                isSomethingUnequal = true;
                i->printData();
                j->printData();
            }
    assert(isSomethingUnequal);
}