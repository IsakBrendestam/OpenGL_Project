#ifndef DEBUG_HEADER
#define DEBUG_HEADER

enum ResourceType
{
    SHADER,
    PROGRAM
};

class Debug
{
public:
    static bool CheckError(unsigned int resource, ResourceType type);
private:

};

#endif