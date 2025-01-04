#ifndef DEBUG_HEADER
#define DEBUG_HEADER

#include <string>

//#define DEBUG

#ifdef DEBUG
    void DebugLog(std::string msg);
#else
    #define DebugLog(msg)
#endif

enum ResourceType
{
    SHADER,
    PROGRAM
};

// Returns true if error is detected
bool CheckError(unsigned int resource, ResourceType type);

#endif