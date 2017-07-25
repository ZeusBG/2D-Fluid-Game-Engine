#include "engine/rendering/Mesh.h"
#include "engine/object/VisualComponent.h"

void Mesh::SetVertices(const AVector<float>& vertices)
{
	m_Vertices = vertices;
}

void Mesh::InitializeBuffers(ID3D11Device* device, VisualComponent* visualComponent)
{
    //Vertex* vertices;
    //unsigned long* indices;
    D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
    D3D11_SUBRESOURCE_DATA vertexData, indexData;
    HRESULT result;

    m_VertexCount = m_Vertices.size() / 2;
    m_IndexCount = m_VertexCount;

    // Create the vertex array.
	AVector<XMFLOAT3> vertices;
	vertices.reserve(m_VertexCount);
   
    // Create the index array.
	//AVector<unsigned int> indices;// = new unsigned long[m_IndexCount];
	//indices.reserve(m_VertexCount);
    // Load the vertex array with data.
	unsigned int indices[] = { 0,2,1, 0,2,3 };
    for (uint32_t i = 0; i < m_VertexCount; i++)
    {
        vertices.push_back(XMFLOAT3(m_Vertices[2 * i], m_Vertices[2 * i + 1], 0.f));

    }
    // Set up the description of the static vertex buffer.
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = sizeof(XMFLOAT3) * m_VertexCount;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = 0;
    vertexBufferDesc.MiscFlags = 0;
    vertexBufferDesc.StructureByteStride = 0;

    // Give the subresource structure a pointer to the vertex data.
    vertexData.pSysMem = vertices.data();
    vertexData.SysMemPitch = 0;
    vertexData.SysMemSlicePitch = 0;

    // Now create the vertex buffer.
    result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_VertexBuffer);
    // Set up the description of the static index buffer.
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof(indices);
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;
    indexBufferDesc.StructureByteStride = 0;

    // Give the subresource structure a pointer to the index data.
    indexData.pSysMem = indices;
    indexData.SysMemPitch = 0;
    indexData.SysMemSlicePitch = 0;

    // Create the index buffer.
    result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_IndexBuffer);
}

void Mesh::RenderBuffers(ID3D11DeviceContext* deviceContext) const
{
    unsigned int stride;
    unsigned int offset;


    // Set vertex buffer stride and offset.
    stride = sizeof(XMFLOAT4);
    offset = 0;

    // Set the vertex buffer to active in the input assembler so it can be rendered.
    deviceContext->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

    // Set the index buffer to active in the input assembler so it can be rendered.
    deviceContext->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

    // Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    return;
}

void Mesh::ReleaseResource()
{
    // Release the index buffer.
    if (m_IndexBuffer)
    {
        m_IndexBuffer->Release();
        m_IndexBuffer = 0;
    }

    // Release the vertex buffer.
    if (m_VertexBuffer)
    {
        m_VertexBuffer->Release();
        m_VertexBuffer = 0;
    }

    return;
}