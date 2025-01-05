#ifndef COLLIDER_HEADER
#define COLLIDER_HEADER

enum ColliderType {
    SPHERE,
    BOX
};

class Collider
{
public:
    Collider(ColliderType type);
    virtual ~Collider();

    virtual bool Intersection(const Collider& other) = 0;

    ColliderType GetType() const;

private:
    ColliderType m_type;
};

#endif