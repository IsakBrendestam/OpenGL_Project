#ifndef CUBE_HEADER
#define CUBE_HEADER

#include "Object.h"

class Cube : public Object
{
public:
    Cube();
    ~Cube();

    void Update(double deltaTime) override;
    void Draw() override;

private:
};

#endif