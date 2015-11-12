#include <iostream>

class vkapi
{
public:
    vkapi();
    ~vkapi();
private:
    void readTokenFromFile();

    std::string token;
};