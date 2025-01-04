#ifndef MESH_HEADER
#define MESH_HEADER

#include <string>
#include <cstring>
#include <cstdlib>

#include "glm/gtc/type_ptr.hpp"

#include "Vertex.h"
#include "Material.h"

struct MeshColor
{
    ShaderVertexColor* g_vertices;
    unsigned int g_nVertices;
    unsigned int* g_indices;
    unsigned int g_nIndices;

    MeshColor(const ShaderVertexColor* vertices, unsigned int nVertices, const unsigned int* indices, unsigned int nIndices):
        g_nVertices(nVertices), g_nIndices(nIndices)
    {
        g_vertices = (ShaderVertexColor*)std::malloc(g_nVertices * sizeof(ShaderVertexColor));
        std::memcpy(g_vertices, vertices, g_nVertices * sizeof(ShaderVertexColor));

        g_indices = (unsigned int*)std::malloc(g_nIndices * sizeof(unsigned int));
        std::memcpy(g_indices, indices, g_nIndices * sizeof(unsigned int));
    }
};

struct MeshTexture
{
    ShaderVertexTexture* g_vertices;
    unsigned int g_nVertices;
    unsigned int* g_indices;
    unsigned int g_nIndices;
    std::string g_textureName;

    MeshTexture(const ShaderVertexTexture* vertices, unsigned int nVertices, const unsigned int* indices, unsigned int nIndices, const std::string& textureName):
        g_nVertices(nVertices), g_nIndices(nIndices), g_textureName(textureName)
    {
        g_vertices = (ShaderVertexTexture*)std::malloc(g_nVertices * sizeof(ShaderVertexTexture));
        std::memcpy(g_vertices, vertices, g_nVertices * sizeof(ShaderVertexTexture));

        g_indices = (unsigned int*)std::malloc(g_nIndices * sizeof(unsigned int));
        std::memcpy(g_indices, indices, g_nIndices * sizeof(unsigned int));
    }

    ~MeshTexture()
    {
        free(g_vertices);
        free(g_indices);
    }
};

struct MeshData
{
	struct VertexInfo
	{
		size_t sizeOfVertex;
		size_t nrOfVerticesInBuffer;
		void* vertexData;
	} vertexInfo;

	struct IndexInfo
	{
		size_t nrOfIndicesInBuffer;
		unsigned int* indexData;
	} indexInfo;

	struct SubMeshInfo
	{
		Material material;
		size_t startIndexValue;
		size_t nrOfIndicesInSubMesh;
	};

	std::vector<SubMeshInfo> subMeshInfo;

    glm::vec3 BBMin, BBMax;    
};

#endif