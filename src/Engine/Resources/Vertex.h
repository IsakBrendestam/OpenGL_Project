#ifndef VERTEX_HEADER
#define VERTEX_HEADER

struct VertexColor
{
    float p_position[3];
    float p_color[3];
};

struct VertexTexture
{
    float p_position[3];
    float p_stCoord[2];
    float p_normal[3];
};


#endif