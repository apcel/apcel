#pragma once
#include <iostream>
#include <fstream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/prettywriter.h"

class portal
{
public:
  void debugJsonErr(rapidjson::Value * JSON);
  portal();
  portal(rapidjson::Value& parent);
  ~portal();
  portal(const portal *);
  portal(const portal &);
  void updateWith(rapidjson::Value &JSON);
  // void parseJSON(rapidjson::Document * JSON);
  // void reset();
  void printData();

private:

  rapidjson::Document json;

  bool fullInfo = false;
  std::string raw = "";
  short resonatorsLevelSum = 0;


  rapidjson::Document parseResonator(rapidjson::Value &arr);
  rapidjson::Document parseMod(rapidjson::Value &arr);
  rapidjson::Document corePortalData(rapidjson::Value &arr);
  rapidjson::Document summaryPortalData(rapidjson::Value &arr);
  rapidjson::Document portalDetail(rapidjson::Value &arr);
public:
  short getResSum();

  std::string getTeam();
  long getLatE6();
  long getLngE6();
  int getLevel();
  double getHealth();
  int getResCount();
  std::string getImage();
  std::string getTitle();
  bool operator < ( portal& that);
  bool operator > ( portal& that);
  void operator = ( portal& that);
  bool hasFullInfo();
};