#ifndef COMPONENT_HEADER
#define COMPONENT_HEADER

class Component 
{
public:
    Component() = default;
    virtual ~Component() = default;

    virtual void Update() = 0;
    virtual void Draw() = 0;
};

#endif