#include "vkapi.h"
vkapi::vkapi(){
    readTokenFromFile();
}
void vkapi::readTokenFromFile(){

    if (FILE *fp = fopen("./token", "r"))
    {
        char buf[1024];
        while (size_t len = fread(buf, 1, sizeof(buf), fp))
            token.insert(token.end(), buf, buf + len);
        fclose(fp);
    }
}