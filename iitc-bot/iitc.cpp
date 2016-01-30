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

    std::cout << response.text << std::endl << std::endl;


    rapidjson::Document jsonResponse;
    jsonResponse.Parse(response.text.c_str());
    if (jsonResponse.HasParseError()) {
        std::cout << response.text << std::endl;
        assert(false);
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