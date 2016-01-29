#include <iostream>

#include <cpr/cpr.h>
// #include <json.hpp>
#include "rapidjson/reader.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/error/en.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

int main(int argc, char** argv) {


    auto response = cpr::Post(
                        cpr::Url{"https://www.ingress.com/r/getPortalDetails"},
                        // cpr::Url{"https://www.ingress.com/r/getEntities"},
    cpr::Header{
        {
            "Cookie", "\
                                    SACSID=AJKiYcFqK2uTFcBy7TWddl-d-FzzyrdVig_P2U4JOi-EnyuvQW4mcwkN77_nruMe0g74Q0RDHAXwVpmm-NcZMPqLdRDkKDglN19NfQTGJRDZhLFBa5NRB4aYrFGG8utq2NlQW86bPyZztUgvej0ubqSOISH-LHglnuZ2ZMyYDmDlJncz6J51e0yUfIUTk1128d0lHJ4fqK2JW3HmKcdi3D-0Ls6iJT1-zgsepzRJtFgVj6rUFY5YRG5F4nAKcnZcA2MpLMhoP8vsmrqLNtM6d7dmLPbz4cM7JPBFx9bRjPPnr3s30ALCkafvNHdnkwBL_IsZ2CU-XIqeA84AtyM4DCooOqaa4EXCXkWSTAWbaxlzNiFyZDNK6f8maHKikC9cghPasHjpZntuzuCc2_yeLZexS-HqIbyyDnOwH2Fru2UPRQE686gh3qybkJP8SqeFKJu3c_1UWRKxH4OYKcqJ7iU44ZJQcOMDiEagPYZ1G5rGaoe2bkAQ4CCfkld_mbbgqUOzc3zVg-rRP2XsYaDrariWnV8YeEu-qb8HOFTGVn_YC9hlTleXNYfYLsTDCTuVt6FF8lhp8_E2RnJJ6H-zJ52nyer7WJ0GiR-bszLuRnluIBncSiwLMF3hluDrYiLp5SNJkXOyxO5rgnwwih7gCKrTO_3hJJwfVA;\
                                    csrftoken=FiJl41mm7Q2WjjchxwZFNwXwsvpqrrO1; \
                                    "
                                    /*
                                    _ga=GA1.2.1072430242.1453277911;\
                                    __utma=24037858.1072430242.1453277911.1454028438.1454031764.18; \
                                    __utmz=24037858.1454028438.17.3.utmcsr=nianticproject.com|utmccn=(referral)|utmcmd=referral|utmcct=/;\
                                    ingress.intelmap.shflt=viz; \
                                    ingress.intelmap.lat=55.78304106721907; \
                                    ingress.intelmap.lng=37.811068296432495; \
                                    ingress.intelmap.zoom=18; \
                                    __utmc=24037858; \
                                    __utmb=24037858.4.9.1454031800981; \
                                    __utmt=1*/
        },
        // {
        //     "Accept", "application/json"
        // },
        {
            "Referer", "https://www.ingress.com/intel"
        },
        {
            "X-CSRFToken", "FiJl41mm7Q2WjjchxwZFNwXwsvpqrrO1"
        }
    },
    // cpr::Body{"{\"tileKeys\":[\"15_19360_9998_0_8_100\"],\"v\":\"9ffe0cfdf367c491a20802d3c606d679992e8b08\"}"}
    // cpr::Body{"{\"guid\":\"b78b0110cafd45aa81c707ba16756de5.16\",\"v\":\"9ffe0cfdf367c491a20802d3c606d679992e8b08\"}"}
    cpr::Body{"{\"guid\":\"fa0838e5401643b6ac6b58b981f3994f.16\",\"v\":\"9ffe0cfdf367c491a20802d3c606d679992e8b08\"}"}
                    );
    std::cout << response.text << std::endl;
    return 0;

    rapidjson::StringStream is(response.text.c_str());
    // // rapidjson::Reader reader;
    rapidjson::Reader reader;
    // char readBuffer[65536];
    // rapidjson::FileReadStream is(stdin, readBuffer, sizeof(readBuffer));

    // Prepare writer and output stream.
    char writeBuffer[65536];
    rapidjson::FileWriteStream os(stdout, writeBuffer, sizeof(writeBuffer));
    rapidjson::PrettyWriter<rapidjson::FileWriteStream> writer(os);

    // JSON reader parse from the input stream and let writer generate the output.
    if (!reader.Parse<rapidjson::kParseValidateEncodingFlag>(is, writer)) {
        fprintf(stderr, "\nError(%u): %s\n", static_cast<unsigned>(reader.GetErrorOffset()), GetParseError_En(reader.GetParseErrorCode()));
        return 1;
    }
    return 0;
}