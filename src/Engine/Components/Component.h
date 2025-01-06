#ifndef COMPONENT_HEADER
#define COMPONENT_HEADER

enum ComponentType
{
    TRANSFORM,
    COLLIDER,
};


class Component 
{
public:
    Component(ComponentType type);
    virtual ~Component() = default;

    ComponentType GetType();

    virtual void Update() = 0;
    virtual void Draw() = 0;

private:
    const ComponentType m_type;
};

#endif