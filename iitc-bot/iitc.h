#pragma once
#include "iostream"
#include <cpr/cpr.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"

class iitc
{
public:
    iitc(std::string SACSID, std::string headerCSRF, std::string cookieCSRF);
    ~iitc();
    rapidjson::Document request(std::string method, std::string params);
    void setCookieSACSID(std::string SACSID);
    void setCSRF(std::string cookie, std::string header);
private:
    std::string cookieSACSID;
    std::string cookieCSRF;
    std::string headerCSRF;
    std::string iitcBaseURL     = "https://www.ingress.com/r/";
};