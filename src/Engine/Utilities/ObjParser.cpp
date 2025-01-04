#include "ObjParser.h"

#include "Debug.h"

ObjParser::ObjParser(std::string folderPath, std::string fileName, bool inverseY):
	m_folderPath(folderPath), m_inverseY(inverseY)
{
	FileHandler(m_folderPath + fileName);

	AddObject();
}

MeshData ObjParser::GetMeshData()
{
	MeshData meshData;

	meshData.vertexInfo.nrOfVerticesInBuffer = m_objectsData[0].vertices.size();
	meshData.vertexInfo.sizeOfVertex = sizeof(ShaderVertexTexture);
	meshData.vertexInfo.vertexData = m_objectsData[0].vertices.data();

	meshData.indexInfo.nrOfIndicesInBuffer = m_objectsData[0].indices.size();
	meshData.indexInfo.indexData = m_objectsData[0].indices.data();

	MeshData::SubMeshInfo subMeshInfo;
	subMeshInfo.material = m_objectsData[0].material;
	subMeshInfo.nrOfIndicesInSubMesh = m_objectsData[0].indices.size();
	subMeshInfo.startIndexValue = 0;

	meshData.subMeshInfo.push_back(subMeshInfo);
	meshData.BBMin = GetBoundingBoxMin();
	meshData.BBMax = GetBoundingBoxMax();

	return meshData;
}

std::vector<Vertex> ObjParser::GetVertecies()
{
	return m_vertecies;
}

std::vector<VertexTexture> ObjParser::GetVertexTextures()
{
	return m_vertexTextures;
}

std::vector<VertexNormal> ObjParser::GetVertexNormals()
{
	return m_vertexNormals;
}

std::vector<Face> ObjParser::GetFaces()
{
	return m_faces;
}

void ObjParser::AddObject()
{
	std::vector<ShaderVertexTexture> vertices;
	std::vector<uint32_t> indices;

	for (int i = 0; i < m_faces.size(); i++)
	{
		for (int j = 0; j < m_faces[i].nSets; j++)
		{
			// Creating vertex
			Vertex v = m_vertecies[m_faces[i].iv[j]];

			// Creating vertex normal
			VertexNormal vn;
			if (m_faces[i].ivn.size() > 0)
				vn = m_vertexNormals[m_faces[i].ivn[j]];
			else
				vn = VertexNormal();

			// Creating vertex texture
			VertexTexture vt;
			if (m_faces[i].ivn.size() > 0)
				vt = m_vertexTextures[m_faces[i].ivt[j]];
			else
				vt = VertexTexture();

			// Creating temporary UV vertex
			ShaderVertexTexture tempVertex = { {v.x, v.y, v.z},
											   {vt.u, vt.v},
										  	   {vn.x, vn.y, vn.z}
										     };

			// Checking if vertex already exists
			uint32_t vertexIndex = FindVertex(tempVertex, vertices);
			if (vertexIndex == vertices.size())
				vertices.push_back(tempVertex);

			indices.push_back(vertexIndex);
		}
	}

	Material material = m_materials[m_currentMaterial];

	m_objectsData.push_back({ vertices, indices, material });
}

void ObjParser::FileHandler(std::string filePath)
{
	std::ifstream file(filePath);

	if (!file.good())
	{
		std::cout << "File: " << filePath << " not found!" << std::endl;
		return;
	}

	std::string line;
	while (std::getline(file, line))
		LineParser(line);
			
	file.close();
}

Vertex ObjParser::ParseVertex(std::string line)
{
	float xPos, yPos, zPos, wPos;
	float rCol, gCol, bCol;

	std::string s;
	std::stringstream ss(line);

	int index = 0;
	while (std::getline(ss, s, ' '))
	{
		float value;
		if (index > 0)
			value = std::stof(s);

		if (index == 1)
			xPos = value;
		else if (index == 2)
			yPos = value;
		else if (index == 3)
			zPos = value;
		else if (index == 4)
			wPos = rCol = value;
		else if (index == 5)
			gCol = value;
		else if (index == 6)
			bCol = value;

		index++;
	}

	if (index == 4)
		return Vertex(xPos, yPos, zPos);
	else if (index == 5)
		return Vertex(xPos, yPos, zPos, wPos);
	else if (index == 7)
		return Vertex(xPos, yPos, zPos, rCol, gCol, bCol);

	return Vertex();
}

VertexTexture ObjParser::ParseVertexTexture(std::string line)
{
	float uPos, vPos, wPos;

	std::string s;
	std::stringstream ss(line);

	int index = 0;
	while (std::getline(ss, s, ' '))
	{
		float value;
		if (index > 0)
			value = std::stof(s);

		if (index == 1)
			uPos = value;
		else if (index == 2)
			if (m_inverseY)
				vPos = 1 - value;
			else
				vPos = value;
		else if (index == 3)
			wPos = value;

		index++;
	}

	if (index == 2)
		return VertexTexture(uPos);
	else if (index == 3)
		return VertexTexture(uPos, vPos);
	else if (index == 4)
		return VertexTexture(uPos, vPos, wPos);

	return VertexTexture();
}

VertexNormal ObjParser::ParseVertexNormal(std::string line)
{
	float xPos, yPos, zPos;

	std::string s;
	std::stringstream ss(line);

	int index = 0;
	while (std::getline(ss, s, ' '))
	{
		float value;
		if (index > 0)
			value = std::stof(s);

		if (index == 1)
			xPos = value;
		else if (index == 2)
			yPos = value;
		else if (index == 3)
			zPos = value;

		index++;
	}

	if (index == 4)
		return VertexNormal(xPos, yPos, zPos);

	return VertexNormal();
}

Face ObjParser::ParseFace(std::string line)
{
	std::vector<uint32_t> vertexIndex, vertexTextureIndex, vertexNormalIndex;

	std::string s;
	std::stringstream ss(line);

	int setIndex = 0;
	int index = 0;
	while (std::getline(ss, s, ' '))
	{
		if (index > 0)
		{
			setIndex = 0;
			std::string sSet;
			std::stringstream ssSet(s);

			while (std::getline(ssSet, sSet, '/'))
			{
				int value = static_cast<uint32_t>(std::stoul(sSet));
				if (setIndex == 0)
					vertexIndex.push_back(value);
				else if (setIndex == 1)
					vertexTextureIndex.push_back(value);
				else if (setIndex == 2)
					vertexNormalIndex.push_back(value);
 				setIndex++;
			}
		}

		index++;
	}

	if (index == vertexIndex.size()+1)
		return Face(vertexIndex, vertexTextureIndex, vertexNormalIndex, vertexIndex.size());

	return Face();
}

float ObjParser::ParseKd(std::string line)
{
	float val1 = 0, val2 = 0, val3 = 0;

	std::string s;
	std::stringstream ss(line);

	int index = 0;
	while (std::getline(ss, s, ' '))
	{
		float value;
		if (index > 0)
			value = std::stof(s);

		if (index == 1)
			val1 = value;
		else if (index == 2)
			val2 = value;
		else if (index == 3)
			val3 = value;

		index++;
	}

	return val1;
}

float ObjParser::ParseKa(std::string line)
{
	float val1 = 0, val2 = 0, val3 = 0;

	std::string s;
	std::stringstream ss(line);

	int index = 0;
	while (std::getline(ss, s, ' '))
	{
		float value;
		if (index > 0)
			value = std::stof(s);

		if (index == 1)
			val1 = value;
		else if (index == 2)
			val2 = value;
		else if (index == 3)
			val3 = value;

		index++;
	}

	return val1;
}

float ObjParser::ParseKs(std::string line)
{
	float val1 = 0, val2 = 0, val3 = 0;

	std::string s;
	std::stringstream ss(line);

	int index = 0;
	while (std::getline(ss, s, ' '))
	{
		float value;
		if (index > 0)
			value = std::stof(s);

		if (index == 1)
			val1 = value;
		else if (index == 2)
			val2 = value;
		else if (index == 3)
			val3 = value;

		index++;
	}

	return val1;
}

float ObjParser::ParseNs(std::string line)
{
	float val = 0;

	std::string s;
	std::stringstream ss(line);

	int index = 0;
	while (std::getline(ss, s, ' '))
	{
		float value;
		if (index > 0)
			value = std::stof(s);

		if (index == 1)
			val = value;

		index++;
	}

	return val;
}

std::string ObjParser::ParseMtl(std::string line)
{
	return line.erase(0, 7);
}

LineType ObjParser::LineCategorizer(std::string line)
{
	if (line.length() < 2)
		return LineType::NONE;

	if (line.substr(0, 6) == "mtllib")
		return LineType::MTLFILE;
	else if (line.substr(0, 6) == "usemtl")
		return LineType::SETMTL;
	else if (line.substr(0, 6) == "newmtl")
		return LineType::NEWMTL;
	else if (line.substr(0, 2) == "Kd")
		return LineType::KDMTL;
	else if (line.substr(0, 2) == "Ka")
		return LineType::KAMTL;
	else if (line.substr(0, 2) == "Ks")
		return LineType::KSMTL;
	else if (line.substr(0, 2) == "Ns")
		return LineType::NSMTL;
	else if (line.substr(0, 2) == "vt")
		return LineType::VERTEXTEXTURE;
	else if (line.substr(0, 2) == "vn")
		return LineType::VERTEXNORMAL;
	else if (line[0] == 'v')
		return LineType::VERTEX;
	else if (line[0] == 'f')
		return LineType::FACE;
	else
		return LineType::NONE;
}

void ObjParser::LineParser(std::string line)
{
	LineType type = LineCategorizer(line);

	switch (type)
	{
	case VERTEX:
		m_vertecies.push_back(ParseVertex(line));
		break;
	case VERTEXTEXTURE:
		m_vertexTextures.push_back(ParseVertexTexture(line));
		break;
	case VERTEXNORMAL:
		m_vertexNormals.push_back(ParseVertexNormal(line));
		break;
	case FACE:
		m_faces.push_back(ParseFace(line));
		break;
	case MTLFILE:
		FileHandler(m_folderPath+ParseMtl(line));
		break;
	case SETMTL:
		m_currentMaterial = line.erase(0, 7);
		break;
	case NEWMTL:
		m_tempMaterialName = line.erase(0, 7);
		m_materials.insert({ m_tempMaterialName, Material() });
		break;
	case KDMTL:
		m_materials[m_tempMaterialName].diffuse = ParseKd(line);
		break;
	case KAMTL:
		m_materials[m_tempMaterialName].ambient = ParseKa(line);
		break;
	case KSMTL:
		m_materials[m_tempMaterialName].specular = ParseKs(line);
		break;
	case NSMTL:
		m_materials[m_tempMaterialName].shininess = ParseNs(line);
	case NONE:
		//std::cout << "None" << std::endl;
		break;
	default:
		break;
	}
}

uint32_t ObjParser::FindVertex(ShaderVertexTexture vertex, const std::vector<ShaderVertexTexture>& vertices)
{
	for (int i = 0; i < vertices.size(); i++)
	{
		if (vertices[i] == vertex)
			return i;
	}

	return vertices.size();
}

glm::vec3 ObjParser::GetBoundingBoxMax()
{
	if (m_vertecies.size() == 0)
		return glm::vec3(0, 0, 0);

	glm::vec3 maxPos(m_vertecies[0].x, m_vertecies[0].y, m_vertecies[0].z);
	for (auto& vertex : m_vertecies)
	{
		maxPos = { maxPos.x > vertex.x ? maxPos.x : vertex.x,
				   maxPos.y > vertex.y ? maxPos.y : vertex.y,
				   maxPos.z > vertex.z ? maxPos.z : vertex.z };
	}

	return maxPos;
}

glm::vec3 ObjParser::GetBoundingBoxMin()
{
	if (m_vertecies.size() == 0)
		return glm::vec3(0, 0, 0);

	glm::vec3 minPos(m_vertecies[0].x, m_vertecies[0].y, m_vertecies[0].z);
	for (auto& vertex : m_vertecies)
	{
		minPos = { minPos.x < vertex.x ? minPos.x : vertex.x,
				   minPos.y < vertex.y ? minPos.y : vertex.y,
				   minPos.z < vertex.z ? minPos.z : vertex.z };
	}

	return minPos;
}