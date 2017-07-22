#pragma once

#include <directxmath.h>
#include "RendererDX11.h"

using namespace DirectX;

class VisualComponent;
class GeometryHandler
{
public:

    struct Vertex
    {
        XMVECTOR position;
        XMVECTOR color;
    };

    void InitializeBuffers(ID3D11Device* device, VisualComponent* visualComponent);
    void RenderBuffers(ID3D11DeviceContext* devcon);
    void ReleaseResource();

private:
    ID3D11Buffer* m_VertexBuffer;
    uint32_t m_VertexCount;

    ID3D11Buffer* m_IndexBuffer;
    uint32_t m_IndexCount;

};