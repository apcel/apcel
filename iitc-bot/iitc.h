#include "iostream"
#include <cpr/cpr.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"

class iitc
{
public:
    iitc();
    ~iitc();
    rapidjson::Document request(std::string method, std::string params);
private:
    std::string cookieSACSID    = "SACSID=AJKiYcFqK2uTFcBy7TWddl-d-FzzyrdVig_P2U4JOi-EnyuvQW4mcwkN77_nruMe0g74Q0RDHAXwVpmm-NcZMPqLdRDkKDglN19NfQTGJRDZhLFBa5NRB4aYrFGG8utq2NlQW86bPyZztUgvej0ubqSOISH-LHglnuZ2ZMyYDmDlJncz6J51e0yUfIUTk1128d0lHJ4fqK2JW3HmKcdi3D-0Ls6iJT1-zgsepzRJtFgVj6rUFY5YRG5F4nAKcnZcA2MpLMhoP8vsmrqLNtM6d7dmLPbz4cM7JPBFx9bRjPPnr3s30ALCkafvNHdnkwBL_IsZ2CU-XIqeA84AtyM4DCooOqaa4EXCXkWSTAWbaxlzNiFyZDNK6f8maHKikC9cghPasHjpZntuzuCc2_yeLZexS-HqIbyyDnOwH2Fru2UPRQE686gh3qybkJP8SqeFKJu3c_1UWRKxH4OYKcqJ7iU44ZJQcOMDiEagPYZ1G5rGaoe2bkAQ4CCfkld_mbbgqUOzc3zVg-rRP2XsYaDrariWnV8YeEu-qb8HOFTGVn_YC9hlTleXNYfYLsTDCTuVt6FF8lhp8_E2RnJJ6H-zJ52nyer7WJ0GiR-bszLuRnluIBncSiwLMF3hluDrYiLp5SNJkXOyxO5rgnwwih7gCKrTO_3hJJwfVA;";
    std::string cookieCSRF      = "csrftoken=FiJl41mm7Q2WjjchxwZFNwXwsvpqrrO1;";
    std::string headerCSRF      = "FiJl41mm7Q2WjjchxwZFNwXwsvpqrrO1";
    std::string iitcBaseURL     = "https://www.ingress.com/r/";
};