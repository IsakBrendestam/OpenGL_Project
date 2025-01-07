#include "MeshComponent.h"

#include "glad.h"
#include <GLFW/glfw3.h>

#include <stb_image/stb_image.h>

#include "Engine/Utilities/Debug.h"

MeshComponent::MeshComponent(const MeshData& mesh):
    Component(ComponentType::MESH), m_mesh(mesh)
{

}

MeshData MeshComponent::GetMesh()
{
    return m_mesh;
}

void MeshComponent::DrawMesh()
{
    glDrawElements(GL_TRIANGLES, m_mesh.indexInfo.nrOfIndicesInBuffer, GL_UNSIGNED_INT, 0);
}

void MeshComponent::Draw()
{

}