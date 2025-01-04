#ifndef VERTEX_HEADER
#define VERTEX_HEADER

struct ShaderVertexLine
{
    float g_position[3];
    float g_color[3];
};


struct ShaderVertexColor
{
    float p_position[3];
    float p_color[3];
    float p_normal[3];
};

struct ShaderVertexTexture
{
    float p_position[3];
    float p_stCoord[2];
    float p_normal[3];

    bool operator==(const ShaderVertexTexture& other) const
	{
		return p_position[0] == other.p_position[0] && p_position[1] == other.p_position[1] && p_position[2] == other.p_position[2] &&
			   p_normal[0] == other.p_normal[0] && p_normal[1] == other.p_normal[1] && p_normal[2] == other.p_normal[2] &&
			   p_stCoord[0] == other.p_stCoord[0] && p_stCoord[1] == other.p_stCoord[1];
	}
};


#endif