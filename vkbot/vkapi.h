#pragma once
#include <iostream>
#include "https.h"
class vkapi
{
public:
    vkapi();
    ~vkapi();

    void groupsGetById();










private:
    void readTokenFromFile();
    https * httpsObject;
    std::string token;


};