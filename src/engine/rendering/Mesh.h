#pragma once

#include <directxmath.h>
#include "RendererDX11.h"
#include "util/Collections.h"

using namespace DirectX;

class VisualComponent;
class Mesh
{
public:
    //TODO remove;
    struct Vertex
    {
        XMVECTOR position;
        XMVECTOR color;
    };

    void InitializeBuffers(ID3D11Device* device, VisualComponent* visualComponent);
    void RenderBuffers(ID3D11DeviceContext* devcon);
    void ReleaseResource();

private:
    AVector<float> m_Vertices;

    ID3D11Buffer* m_VertexBuffer;
    uint32_t m_VertexCount;

    ID3D11Buffer* m_IndexBuffer;
    uint32_t m_IndexCount;

};