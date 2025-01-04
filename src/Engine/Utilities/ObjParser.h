#ifndef OBJPARSER_HEADER
#define OBJPARSER_HEADER

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

#include "glm/gtc/type_ptr.hpp"

//#include "Engine/D3D11Classes/VertexBufferD3D11.h"
#include "Engine/Resources/Vertex.h"
#include "Engine/Resources/Material.h"
#include "Engine/Resources/Mesh.h"

enum LineType
{
	VERTEX,
	VERTEXTEXTURE,
	VERTEXNORMAL,
	FACE,
	MTLFILE,
	SETMTL,
	NEWMTL,
	KDMTL,
	KAMTL,
	KSMTL,
	NSMTL,
	NONE
};

struct Vertex {
	Vertex() :
		x(0), y(0), z(0), w(1), r(0), g(0), b(0) {};
	Vertex(float xPos, float yPos, float zPos) :
		x(xPos), y(yPos), z(zPos), w(1), r(0), g(0), b(0) {};
	Vertex(float xPos, float yPos, float zPos, float wPos) :
		x(xPos), y(yPos), z(zPos), w(wPos), r(0), g(0), b(0) {};
	Vertex(float xPos, float yPos, float zPos, float rColor, float gColor, float bColor) :
		x(xPos), y(yPos), z(zPos), w(1), r(rColor), g(gColor), b(bColor) {};

	bool operator==(const Vertex& other) const
	{
		return x == other.x && y == other.y && z == other.z && w == other.w && 
			   r == other.r && g == other.g && b == other.b;
	}

	float x, y, z, w;
	float r, g, b;
};

struct VertexTexture {
	VertexTexture() :
		u(0), v(0), w(0) {};
	VertexTexture(float uPos) :
		u(uPos), v(0), w(0) {};
	VertexTexture(float uPos, float vPos) :
		u(uPos), v(vPos), w(0) {};
	VertexTexture(float uPos, float vPos, float wPos) :
		u(uPos), v(vPos), w(wPos) {};

	float u, v, w;
};

struct VertexNormal {
	VertexNormal() :
		x(1), y(1), z(1) {};
	VertexNormal(float xPos, float yPos, float zPos) :
		x(xPos), y(yPos), z(zPos) {};

	float x, y, z;
};

struct Face {
	Face()
	{
		nSets = 0;
	};

	Face(std::vector<uint32_t> vertexIndex, std::vector<uint32_t> vertexTextureIndex, std::vector<uint32_t> vertexNormalIndex, int nrOfSets)
	{
		nSets = nrOfSets;

		for (int i = 0; i < nSets; i++)
		{
			iv.push_back(vertexIndex[i]-1);

			if (vertexTextureIndex.size() > 0)
				ivt.push_back(vertexTextureIndex[i] - 1);

			if (vertexNormalIndex.size() > 0)
				ivn.push_back(vertexNormalIndex[i] - 1);
		}
	};

	std::vector<uint32_t> iv, ivt, ivn;
	int nSets;
};

struct ObjectData {
	std::vector<ShaderVertexTexture> vertices;
	std::vector<uint32_t> indices;
	Material material;
};

class ObjParser
{
public:
	ObjParser() = default;
	ObjParser(std::string folderPath, std::string fileName, bool inverseY = true);

	MeshData GetMeshData();

	std::vector<Vertex> GetVertecies();
	std::vector<VertexTexture> GetVertexTextures();
	std::vector<VertexNormal> GetVertexNormals();
	std::vector<Face> GetFaces();

	void FileHandler(std::string filePath);

private:
	void AddObject();

	Vertex ParseVertex(std::string line);
	VertexTexture ParseVertexTexture(std::string line);
	VertexNormal ParseVertexNormal(std::string line);
	Face ParseFace(std::string line);

	float ParseKd(std::string line);
	float ParseKa(std::string line);
	float ParseKs(std::string line);
	float ParseNs(std::string line);

	std::string ParseMtl(std::string line);

	LineType LineCategorizer(std::string line);
	void LineParser(std::string line);

	uint32_t FindVertex(ShaderVertexTexture vertex, const std::vector<ShaderVertexTexture>& vertices);

	glm::vec3 GetBoundingBoxMax();
	glm::vec3 GetBoundingBoxMin();
	 
private:
	std::vector<Vertex> m_vertecies;
	std::vector<VertexTexture> m_vertexTextures;
	std::vector<VertexNormal> m_vertexNormals;
	std::vector<Face> m_faces;

	std::string m_currentMaterial;

	std::map<std::string, Material> m_materials;

	std::string m_tempMaterialName;

	std::string m_folderPath;

	std::vector<ObjectData> m_objectsData;

	bool m_inverseY;
};

#endif