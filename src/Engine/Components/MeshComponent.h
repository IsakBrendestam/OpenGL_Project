#ifndef MESHCOMPONENT_HEADER
#define MESHCOMPONENT_HEADER

#include "Engine/Resources/Mesh.h"

#include "Component.h"

class MeshComponent: public Component
{
public:
    MeshComponent(const MeshData& mesh);
    ~MeshComponent() = default;

    MeshData GetMesh();
    void DrawMesh();

    void Draw() override;

private:
    MeshData m_mesh;
};

#endif