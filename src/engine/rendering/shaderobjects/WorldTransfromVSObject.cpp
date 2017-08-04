#include "engine/rendering/shaderobjects/WorldTransformVSObject.h"
#include "engine/rendering/RendererDX11.h"
#include "engine/core/Engine.h"

#include "util/math/MathUtils.h"
#include <d3dcompiler.h>

void WorldTransformVSObject::Init()
{
    RendererDX11* renderer = Engine::GetEngine()->GetModule<RendererDX11>();
    if (!renderer)
    {
        //TODO add log messsage after logger is merged
        return;
    }
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    UINT numElements = ARRAYSIZE(layout);
    m_VSData = renderer->CreateVSFromFile(m_FileName.c_str(), layout, numElements, ShaderVersion::V4_0);
    m_MatrixBuffer = renderer->CreateConstantBuffer(sizeof (MatrixBufferType));
}

void WorldTransformVSObject::Destroy()
{
    auto renderer = Engine::GetEngine()->GetModule<RendererDX11>();
    Engine::GetEngine()->GetModule<RendererDX11>()->DestroyVS(m_VSData);
}

void WorldTransformVSObject::BindData(ID3D11DeviceContext* context)
{
    context->VSSetShader(static_cast<ID3D11VertexShader*>(m_VSData.VSPtr), nullptr, 0);
    context->IASetInputLayout(static_cast<ID3D11InputLayout*>(m_VSData.LayoutPtr));
}

void WorldTransformVSObject::UpdateShaderParams(ID3D11DeviceContext* deviceContext, const Mat3x3& worldMatrix)
{
    HRESULT result;
    D3D11_MAPPED_SUBRESOURCE mappedResource;
    MatrixBufferType* dataPtr;
    unsigned int bufferNumber;

    // Transpose the matrices to prepare them for the shader.
    Mat3x3 transposedWorldMatrix = MathUtils::Transpose(worldMatrix);

    // Lock the constant buffer so it can be written to.
    result = deviceContext->Map(m_MatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
 
    // Get a pointer to the data in the constant buffer.
    dataPtr = (MatrixBufferType*)mappedResource.pData;

    // Copy the matrices into the constant buffer.
    dataPtr->world = transposedWorldMatrix.ToXMMATRIX();
    //dataPtr->view = viewMatrix;
    //dataPtr->projection = projectionMatrix;

    // Unlock the constant buffer.
    deviceContext->Unmap(m_MatrixBuffer, 0);

    // Set the position of the constant buffer in the vertex shader.
    bufferNumber = 0;

    // Finanly set the constant buffer in the vertex shader with the updated values.
    deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_MatrixBuffer);
}
