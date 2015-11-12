#pragma once
#include "vkapi.h"
vkapi::vkapi() {
    setup(new https);
}
vkapi::vkapi(https * httpsObjectReceived) {
    setup(httpsObjectReceived);
}
vkapi::~vkapi() {
    httpsObject->~https();
}
void vkapi::setup(https * httpsObjectReceived) {
    readTokenFromFile();
    this->httpsObject = httpsObjectReceived;
}
void vkapi::readTokenFromFile() {

    if (FILE *fp = fopen("./token", "r"))
    {
        char buf[1024];
        while (size_t len = fread(buf, 1, sizeof(buf), fp))
            token.insert(token.end(), buf, buf + len);
        fclose(fp);
    }
}
void vkapi::request(vk method, vk parameters) {
    // fprintf(stderr, "%s\n", "request");
    httpsObject->request("https://api.vk.com/method/" + method + "?" + parameters + "&access_token=" + token);
}
//////////////////////////////////////////////////////////////////////////////
void vkapi::save() {
    save("example.json");
}

void vkapi::save(std::string filename) {
    
}



void vkapi::groupsGetById(vk group_ids) {
    // fprintf(stderr, "%s\n", "groupsGetById(1)");
    groupsGetById(group_ids, "");
}

void vkapi::groupsGetById(vk group_ids, vk fields) {
    // fprintf(stderr, "%s\n", "groupsGetById(2)");
    request("groups.getById", "group_ids=" + group_ids + "fields=" + fields);

}
