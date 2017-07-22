#include "GeometryHandler.h"
#include "../object/VisualComponent.h";

void GeometryHandler::InitializeBuffers(ID3D11Device* device, VisualComponent* visualComponent)
{
    Vertex* vertices;
    unsigned long* indices;
    D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
    D3D11_SUBRESOURCE_DATA vertexData, indexData;
    HRESULT result;

    vector<Vec2>& verticesFromComponent = visualComponent->GetVertices();
    m_VertexCount = verticesFromComponent.size();
    m_IndexCount = m_VertexCount;

    // Create the vertex array.
    vertices = new Vertex[m_VertexCount];
   
    // Create the index array.
    indices = new unsigned long[m_IndexCount];
   
    // Load the vertex array with data.
    for (uint32_t i = 0; i < m_VertexCount; i++)
    {
        vertices[i].position = XMVectorSet(verticesFromComponent[i].x, verticesFromComponent[i].y, 0.f, 0.f);
        indices[i] = i;
    }

    // Set up the description of the static vertex buffer.
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = sizeof(Vertex)* m_VertexCount;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = 0;
    vertexBufferDesc.MiscFlags = 0;
    vertexBufferDesc.StructureByteStride = 0;

    // Give the subresource structure a pointer to the vertex data.
    vertexData.pSysMem = vertices;
    vertexData.SysMemPitch = 0;
    vertexData.SysMemSlicePitch = 0;

    // Now create the vertex buffer.
    result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_VertexBuffer);
   
    // Set up the description of the static index buffer.
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof(unsigned long)* m_IndexCount;
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

    // Release the arrays now that the vertex and index buffers have been created and loaded.
    delete[] vertices;
    vertices = 0;

    delete[] indices;
    indices = 0;
}

void GeometryHandler::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
    unsigned int stride;
    unsigned int offset;


    // Set vertex buffer stride and offset.
    stride = sizeof(Vertex);
    offset = 0;

    // Set the vertex buffer to active in the input assembler so it can be rendered.
    deviceContext->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

    // Set the index buffer to active in the input assembler so it can be rendered.
    deviceContext->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

    // Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    return;
}

void GeometryHandler::ReleaseResource()
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