#pragma once
#include <iostream>
#include "https.h"
class vkapi
{
    typedef std::string vk;
public:
    vkapi();
    vkapi(https *);
    ~vkapi();

    void groupsGetById(vk);
    void groupsGetById(vk, vk);
    void groupsGetMembers(vk, vk, vk, vk, vk, vk);
    void groupsGetMembers(vk, vk);
    void usersGet(vk, vk, vk);
    void usersGet(vk);
    void groupsGet(vk, vk, vk, vk, vk, vk);
    void groupsGet(vk, vk);






    void save();
    void save(std::string);
private:
    void setup(https *);
    void request(vk, vk);
    void readTokenFromFile();
    https * httpsObject;
    std::string token;


};