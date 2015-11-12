#include <iostream>
#include "https.h"
class vkapi
{
public:
    vkapi();
    ~vkapi();
private:
    void readTokenFromFile();
    https * httpsObject;
    std::string token;
};