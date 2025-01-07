#include "Sphere.h"

#include "Engine/Utilities/ObjParser.h"
#include "Engine/Utilities/Debug.h"

Sphere::Sphere(glm::vec3 position, float radius):
    Object(), m_radius(radius)
{
    m_color = {0.4f, 0.4f, 0.4f};
    ObjParser obj("res/Objects/", "Sphere.obj");
    m_mesh = obj.GetMeshData();
    Object::Init(m_color, m_mesh, position, {0, 0, 0}, {radius, radius, radius});

    AddComponent(new ColliderComponent());
    GetComponent<ColliderComponent>()->AssignSphereCollider(position, radius);

    AddComponent(new MeshComponent(m_mesh));
}

void Sphere::Update(double deltaTime)
{

}

void Sphere::OnCollision(const ComponentObject& other)
{
    UpdateColor({1.0f, 0.0f, 0.0f});
}

void Sphere::Draw()
{
    m_shader.Use();

    glBindTexture(GL_TEXTURE_2D, m_texture);
    glBindVertexArray(m_VAO);
    GetComponent<MeshComponent>()->DrawMesh();
    //glDrawElements(GL_TRIANGLES, m_mesh.indexInfo.nrOfIndicesInBuffer, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
