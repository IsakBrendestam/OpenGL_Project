#ifndef LINE_HEADER
#define LINE_HEADER

#include <vector>

#include "Object.h"

class Line : public Object
{
public:
    Line(const std::vector<glm::vec3>& positions, const glm::vec3& color);
    ~Line();

    void Update(double deltaTime) override;
    void Draw() override;

private:
    unsigned int m_nVertices;
    unsigned int m_nIndices;
};

#endif