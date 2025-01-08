#ifndef DEBUG_HEADER
#define DEBUG_HEADER

#include <vector>
#include <string>

//#define DEBUG

class Debug
{
public:
    static std::vector<std::string> g_debugLog;

};

#ifdef DEBUG
    #define DebugLog(msg) {DebugMessage(msg, __LINE__, __FILE__);}
    void DebugMessage(std::string msg, int line, const char* file);
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