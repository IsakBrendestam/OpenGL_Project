#ifndef INSPECTORCOMPOENTN_HEADER
#define INSPECTORCOMPOENTN_HEADER

#include <string>

class InspectorComponent
{
public: 
    InspectorComponent() = default;
    InspectorComponent(const std::string& name);

    std::string GetName() const;
    void SetName(const std::string& name);

    virtual void DrawInspector() = 0;

private:
    std::string m_name;
};

#endif