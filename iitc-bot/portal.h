#pragma once
#include <iostream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"

class portal
{
private:
  class modInfo
  {
  public:
    std::string owner;
    std::string name;
    std::string rarity;
    class statsStruct
    {
    public:
      long removal_stickiness = 0;
      short mitigation = 0;
      short burnout_insulation = 0;
      long hack_speed = 0;
      int force_amplifier = 0;
      long hit_bonus = 0;
      int attack_frequency = 0;
      short outgoing_links = 0;
    } stats;
  };

  class resonator {
  public:
    std::string owner = "";
    short level = 0;
    int energy = 0;
  };
  bool parseArray(rapidjson::Value * JSON);
  bool parseObject(rapidjson::Value * JSON);
  void debugJsonErr(rapidjson::Value * JSON);
public:
  portal();
  ~portal();
  bool parseJSON(rapidjson::Value * JSON);
  // void parseJSON(rapidjson::Document * JSON);
  void reset();
  void printData();

private:
  rapidjson::Document json;
  std::string uid = "";
  std::string team = "";
  long latE6 = 0;
  long lngE6 = 0;
  short level = 0;
  double health = 0;
  short resCount = 0;
  std::string image = "";
  std::string title = "";
  long long timestamp = 0;
  modInfo mods[4];
  resonator resonators[8];
  std::string owner = "";

  bool fullInfo = false;
  std::string raw = "";
  short resonatorsLevelSum = 0;
};
/*
"team": "R",
  "latE6": 55788569,
  "lngE6": 37783879,
  "level": 8,
  "health": 100,
  "resCount": 8,
  "image": "http://lh5.ggpht.com/1tQBSX9Q6hA-0kDdlRimtNG93GCdCdEnnxhEmbOvKjOqSeGHntrHa-3FCVOl6GRT09lb0mL3qunke5Ctam4e",
  "title": "Magazin Riba",
  "ornaments": [],
  "mission": false,
  "mission50plus": false,
  "artifactBrief": null,
  "timestamp": 1454142636594,
  "mods": [
    {
      "owner": "glipka",
      "name": "Portal Shield",
      "rarity": "RARE",
      "stats": {
        "REMOVAL_STICKINESS": "150000",
        "MITIGATION": "40"
      }
    },
    {
      "owner": "Yussya",
      "name": "Multi-hack",
      "rarity": "RARE",
      "stats": {
        "BURNOUT_INSULATION": "8",
        "REMOVAL_STICKINESS": "0"
      }
    },
    {
      "owner": "QueenWitch",
      "name": "Multi-hack",
      "rarity": "COMMON",
      "stats": {
        "BURNOUT_INSULATION": "4",
        "REMOVAL_STICKINESS": "0"
      }
    },
    {
      "owner": "Yussya",
      "name": "Heat Sink",
      "rarity": "RARE",
      "stats": {
        "REMOVAL_STICKINESS": "0",
        "HACK_SPEED": "500000"
      }
    }
  ],
  "resonators": [
    {
      "owner": "Vorchunishka",
      "level": 8,
      "energy": 6000
    },
    {
      "owner": "Yussya",
      "level": 8,
      "energy": 6000
    },
    {
      "owner": "QueenWitch",
      "level": 8,
      "energy": 6000
    },
    {
      "owner": "RustyCageMan",
      "level": 8,
      "energy": 6000
    },
    {
      "owner": "psybrat",
      "level": 8,
      "energy": 6000
    },
    {
      "owner": "MaryStray",
      "level": 8,
      "energy": 6000
    },
    {
      "owner": "glipka",
      "level": 8,
      "energy": 6000
    },
    {
      "owner": "Rozhok",
      "level": 8,
      "energy": 6000
    }
  ],
  "owner": "QueenWitch",
  "artifactDetail": null
}
*/