#ifndef RECTANGLE_HEADER
#define RECTANGLE_HEADER

#include "Object.h"

class Rectangle : public Object
{
public:
    Rectangle();
    ~Rectangle();

    void Update() override;
    void Draw() override;

private:
};

#endif