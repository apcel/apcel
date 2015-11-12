#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    std::string jsonString;
    if (FILE *fp = fopen("filename", "r"))
    {
        char buf[1024];
        while (size_t len = fread(buf, 1, sizeof(buf), fp))
            jsonString.insert(jsonString.end(), buf, buf + len);
        fclose(fp);
    }
    int findInt;
    std::string responseString = "\"response\":";
    findInt = jsonString.find(responseString);
    std::string tempString;
    if (findInt != jsonString.npos) {
        jsonString = jsonString.substr(findInt + responseString.size(), jsonString.npos);
        // std::cout << jsonString;
        if (jsonString.front() == '[') {
            jsonString = jsonString.substr(1, jsonString.npos);
            while (jsonString.front() != ',') {
                tempString.push_back(jsonString.front());
                jsonString = jsonString.substr(1, jsonString.npos);
            };
        } else if (jsonString.front() == '{') {fprintf(stderr, "%s\n", "ШАЙТАНАМА!!!"); return -100;}
        int numberOfEntities;
        numberOfEntities = stoi(tempString, 0, 10);
        // std::cout << numberOfEntities;
        if (numberOfEntities == 1000 || numberOfEntities == 200) {/*Проблемы, надо докачивать. Причём не константами это должно быть. */}

        std::string gidString = "\"gid\":";
        while ((findInt = jsonString.find(gidString)) != jsonString.npos) {
            tempString.clear();
            jsonString = jsonString.substr(findInt + gidString.size(), jsonString.npos);

            jsonString = jsonString.substr(0, jsonString.npos);
            while (jsonString.front() != ',') {
                tempString.push_back(jsonString.front());
                jsonString = jsonString.substr(1, jsonString.npos);
            };
            int gid = stoi(tempString, 0, 10);
            std::cout << gid << std::endl;
        }

    }
    return 0;
}