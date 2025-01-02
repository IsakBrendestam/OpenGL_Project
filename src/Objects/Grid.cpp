#include "Grid.h"

Grid::Grid(unsigned int nSeperators, float maxSpace): Object()
{
    float tileSpace = maxSpace/(float)nSeperators;
    float nOffset = (float)nSeperators/2;
    for (float i = -nOffset; i <= nOffset; i++)
    {
        m_lines.push_back(new Line({{-maxSpace/2, 0, tileSpace*i}, {maxSpace/2, 0, tileSpace*i}}, 
                                    {0.7f, 0.7f, 0.7f}));

        m_lines.push_back(new Line({{tileSpace*i, 0, -maxSpace/2}, {tileSpace*i, 0, maxSpace/2}}, 
                                    {0.7f, 0.7f, 0.7f}));
    }
}

Grid::~Grid()
{
    for(auto& line : m_lines) 
        delete line;
}

void Grid::Update(double deltaTime)
{
    for(auto& line : m_lines) 
        line->Update(deltaTime);
}

void Grid::Draw()
{
    for(auto& line : m_lines) 
        line->Draw();
}