#pragma once

#include <directxmath.h>
#include "RendererDX11.h"
#include "util/Collections.h"

using namespace DirectX;

class VisualComponent;
class Mesh
{
public:
    void SetVertices(const AVector<XMFLOAT2>& vertices);
    void AddVertex(float x, float y);
    void InitializeBuffers(ID3D11Device* device, VisualComponent* visualComponent);
    void RenderBuffers() const;
    void ReleaseResource();
    void SetIndices(const AVector<unsigned int> indices) { m_Indices = indices; }
    void AddIndex(unsigned int i1, unsigned int i2, unsigned int i3);
    unsigned GetVerticesCount() const { return m_Vertices.size(); }
    unsigned GetIndicesCount() const { return m_Indices.size(); }
private:
    AVector<XMFLOAT2> m_Vertices;
    AVector<unsigned int> m_Indices;

    ID3D11Buffer* m_VertexBuffer;

    ID3D11Buffer* m_IndexBuffer;

};