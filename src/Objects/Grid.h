#ifndef GRID_HEADER
#define GRID_HEADER

#include <vector>

#include "Object.h"
#include "Line.h"

class Grid : public Object
{
public:
    Grid(unsigned int nSeperators, float maxSpace);
    ~Grid();

    void Update(double deltaTime) override;
    void Draw() override;

private:
    std::vector<Line*> m_lines;
};

#endif