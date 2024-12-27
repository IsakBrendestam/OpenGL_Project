#ifndef MESH_HEADER
#define MESH_HEADER

#include "Vertex.h"

#include <string>
#include <cstring>
#include <cstdlib>

#include "Utilities/Debug.h"

struct MeshColor
{
    VertexColor* p_vertices;
    unsigned int p_nVertices;
    unsigned int* p_indices;
    unsigned int p_nIndices;

    MeshColor(const VertexColor* vertices, unsigned int nVertices, const unsigned int* indices, unsigned int nIndices):
        p_nVertices(nVertices), p_nIndices(nIndices)
    {
        p_vertices = (VertexColor*)std::malloc(p_nVertices * sizeof(VertexColor));
        std::memcpy(p_vertices, vertices, p_nVertices * sizeof(VertexColor));

        p_indices = (unsigned int*)std::malloc(p_nIndices * sizeof(unsigned int));
        std::memcpy(p_indices, indices, p_nIndices * sizeof(unsigned int));
    }
};

struct MeshTexture
{
    VertexTexture* p_vertices;
    unsigned int p_nVertices;
    unsigned int* p_indices;
    unsigned int p_nIndices;
    std::string p_textureName;

    MeshTexture(const VertexTexture* vertices, unsigned int nVertices, const unsigned int* indices, unsigned int nIndices, const std::string& textureName):
        p_nVertices(nVertices), p_nIndices(nIndices), p_textureName(textureName)
    {
        p_vertices = (VertexTexture*)std::malloc(p_nVertices * sizeof(VertexTexture));
        std::memcpy(p_vertices, vertices, p_nVertices * sizeof(VertexTexture));

        p_indices = (unsigned int*)std::malloc(p_nIndices * sizeof(unsigned int));
        std::memcpy(p_indices, indices, p_nIndices * sizeof(unsigned int));
    }

    ~MeshTexture()
    {
        free(p_vertices);
        free(p_indices);
    }
};

#endif