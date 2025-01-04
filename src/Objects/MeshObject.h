#ifndef MESHOBJECT_HEADER
#define MESHOBJECT_HEADER

#include "Object.h"

class MeshObject : public Object
{
public:
    MeshObject(MeshData mesh, const std::string& textureName, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
    MeshObject(glm::vec3 color, MeshData mesh, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
    ~MeshObject();

    void Update(double deltaTime) override;
    void Draw() override;

private:
    MeshData m_mesh;
};

#endif