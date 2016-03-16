#include "multiplePortals.h"


bool multiplePortals::acceptGEOJSON(std::string geoJSONString) {
    // rapidjson::Document geoJSON;
    // geoJSON.Parse(geoJSONString.c_str());

    std::cerr << "Not implemented!" << std::endl;
    exit(1);
    return true;
}

bool multiplePortals::acceptIITCPolygon(std::string copyPolygons) {
    // portal debugger;
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
// std::cout << "here";

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
                std::vector<long long> pointTilesX; //swapped :(
                std::vector<long long> pointTilesY;
                iitc intel(jsonSettingsFile);
                for (auto xPoint : polygon->polyX) {
                    pointTilesY.push_back(intel.latToTile(xPoint * 1e6, intel.TILES_PER_EDGE[15]));
                    // std::cout << pointTilesX.back() << std::endl;
                }
                for (auto yPoint : polygon->polyY)
                    pointTilesX.push_back(intel.lngToTile(yPoint * 1e6, intel.TILES_PER_EDGE[15]));
                std::sort(pointTilesX.begin(), pointTilesX.end());
                std::sort(pointTilesY.begin(), pointTilesY.end());


                //construct request of squares 3x3
                short squareSide = 3;

                long long i = pointTilesX.front();
                while (i < pointTilesX.back()) {
                    long long j = pointTilesY.front();
                    while (j < pointTilesY.back()) {
                        // for (long long i = pointTilesX.front(); i <= pointTilesX.back(); i++)
                        // for (long long j = pointTilesY.front(); j <= pointTilesY.back(); j++)
                        for (short k = 0; k < squareSide; k++) {
                            for (short l = 0; l < squareSide; l++) {

                                {
                                    polygon->tiles.push_back(intel.pointToTileId(i + k, j + l, 15, 0));

                                }
                            }
                        }//for
                        j += squareSide;
                    }
                    i += squareSide;
                }//while
                // // print it
                // for (auto i : polygon->tiles)
                //     std::cout << i << std::endl;
                // // and save
                this->pocessedPolygons.push_back(polygon);
            } else {
                delete polygon;
            }
        };// cycle through polygons
    } else {
        std::cerr << "Got a json, root object of which is not an array!" << std::endl;
    }
    if (pocessedPolygons.empty())
        return false;
    else
        return true;
}

void multiplePortals::process() {
    iitc intel(jsonSettingsFile);
    for (auto polygon : pocessedPolygons) {
        std::vector < portal * > fetched = intel.fetchPortals(polygon->tiles);
        std::vector < portal * > got;
        precalc_values(polygon);
        for (auto i : fetched) {
            if (pointInPolygon(polygon, i->getLatE6() / 1e6, i->getLngE6() / 1e6)) {
                got.push_back(i);
                if (!strcasecmp(got.back()->getTeam().c_str(), "E"))
                    portalsWithLevel[i->getLevel()][0]++;
                else if (!strcasecmp(got.back()->getTeam().c_str(), "R"))
                    portalsWithLevel[i->getLevel()][1]++;
                else
                    portalsWithLevel[0][0]++;

            }
        }


        gotPortals.insert( gotPortals.end(), got.begin(), got.end() );
    }

    // std::cout << "got " << gotPortals.size() << " portals\n";
}



void multiplePortals::precalc_values(portalsInPolygon * polygon) {

    polygon->constant.reserve(polygon->polyCorners);
    polygon->multiple.reserve(polygon->polyCorners);
    int   i, j = polygon->polyCorners - 1 ;

    for (i = 0; i < polygon->polyCorners; i++) {
        if (polygon->polyY[j] == polygon->polyY[i]) {
            polygon->constant[i] = polygon->polyX[i];
            polygon->multiple[i] = 0;
        }
        else {
            polygon->constant[i] = polygon->polyX[i] - (polygon->polyY[i] * polygon->polyX[j]) / (polygon->polyY[j] - polygon->polyY[i]) + (polygon->polyY[i] * polygon->polyX[i]) / (polygon->polyY[j] - polygon->polyY[i]);
            polygon->multiple[i] = (polygon->polyX[j] - polygon->polyX[i]) / (polygon->polyY[j] - polygon->polyY[i]);
        }
        j = i;
    }
}

bool multiplePortals::pointInPolygon(portalsInPolygon * polygon, double x, double y) {

    int   i, j = polygon->polyCorners - 1;
    bool  oddNodes = false;

    for (i = 0; i < polygon->polyCorners; i++) {
        if (false
                ||  (polygon->polyY[i] < y && polygon->polyY[j] >= y)
                ||  (polygon->polyY[j] < y && polygon->polyY[i] >= y)
           ) {
            oddNodes ^= (y * polygon->multiple[i] + polygon->constant[i] < x);
        }
        j = i;
    }

    return oddNodes;
}






void multiplePortals::highestLevel(int numberOfSuch) {
    std::sort(gotPortals.begin(), gotPortals.end(), less() );
    for (int i = gotPortals.size() - numberOfSuch; i < gotPortals.size() ; ++i)
    {
        // gotPortals[i]->printData();
        std::cout << "Title:" << gotPortals[i]->getTitle() << std::endl;
        std::cout << "Level:" << gotPortals[i]->getLevel() << std::endl;
    }
};
void multiplePortals::atLevel(short level) {

    for (int i = 0; i < gotPortals.size(); i++)
    {
        if (gotPortals[i]->getLevel() == level) {
            // gotPortals[i]->printData();
            std::cout << "Title:" << gotPortals[i]->getTitle() << std::endl;
            std::cout << "Level:" << gotPortals[i]->getLevel() << std::endl;
        }
    }
};
void multiplePortals::wtf() {
    std::cout << "\tE•R" << std::endl;
    for (int i = 8; i > 0; i--)
    {
        std::cout << "L" + std::to_string(i) + " ► " + std::to_string(portalsWithLevel[i][0])\
                  + "  \t" + std::to_string(portalsWithLevel[i][1]) << std::endl;
    }
    std::cout << "Uncaptured : " + std::to_string(portalsWithLevel[0][0]) << std::endl;

    // bool isSomethingUnequal = false;
    // for(portal * i:gotPortals)
    //     for(portal * j:gotPortals)
    //         if(i != j) {
    //             isSomethingUnequal = true;
    //             i->printData();
    //             j->printData();
    //         }
    // assert(isSomethingUnequal);
}
