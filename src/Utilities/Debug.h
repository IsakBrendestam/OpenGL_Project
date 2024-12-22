#ifndef DEBUG_HEADER
#define DEBUG_HEADER

#include <string>
#include <iostream>
#include <ctime>

#define DEBUG

#ifdef DEBUG
    inline void DebugLog(char* msg)
    {
        time_t now = std::time(0);
        tm* ltm = std::localtime(&now);

        std::string timestamp = "[" + std::to_string(5 + ltm->tm_hour) + ":" + std::to_string(ltm->tm_min) + ":" + std::to_string(ltm->tm_sec) + "] ";

        std::cout << timestamp << msg << std::endl;

    }
#else
    #define DebugLog(msg)
#endif


#endif