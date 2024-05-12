//
// Created by topto on 2024-05-12.
//

#ifndef CPP_2024_1_PROJEKTAS_FRONT_BACK_PROXY_H
#define CPP_2024_1_PROJEKTAS_FRONT_BACK_PROXY_H


#include <string>
#include <chrono>

class front_back_proxy {
public:
    static void beginEntry(std::string name, std::chrono::time_point<std::chrono::system_clock> time, std::string comment);
    static void endEntry(std::chrono::time_point<std::chrono::system_clock> time);
    static void pauseEntry(std::chrono::time_point<std::chrono::system_clock> time);
    static bool isEntryActive();
    static bool isEntryPaused();
    static long long getActiveEntryTime();
    static std::string getActiveEntryName();
    static void initFile(std::string path);
    static void saveToFile();
    static void loadFromFile();
private:
    struct fbProxyImpl;
    fbProxyImpl* ptr;
};


#endif //CPP_2024_1_PROJEKTAS_FRONT_BACK_PROXY_H
