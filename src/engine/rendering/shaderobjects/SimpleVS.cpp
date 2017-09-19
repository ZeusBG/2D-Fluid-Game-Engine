#pragma once

#include "engine/core/Engine.h"
#include "engine/rendering/shaderobjects/SimpleVS.h"
#include "engine/rendering/RenderCommander.h"
#include "engine/rendering/RendererDX11.h"

#include "engine/object/basecomponents/VisualComponent.h"

#include "util/math/MathUtils.h"

#include "engine/camera/CameraHandler.h"

#include <d3d11_1.h>
#include <d3dcompiler.h>

IMPLEMENT_METADATA(SimpleVS);

struct WVP
{
    XMMATRIX m_WMat;
    XMMATRIX m_VMat;
    XMMATRIX m_PMat;

};

void SimpleVS::Init()
{
    auto renderer = Engine::GetEngine()->GetModule<RendererDX11>();
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
    m_VSShader = renderer->CreateVSFromFile(m_FileName.c_str(), layout, numElements, ShaderVersion::V4_0);

    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(WVP);
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bd.CPUAccessFlags = 0;
    auto renderCommander = Engine::GetEngine()->GetModule<RenderCommanderDx11>();
    renderCommander->CreateBuffer(&bd, nullptr, &m_WorldMatrix);
}

void SimpleVS::Destroy()
{
    auto renderCommander = Engine::GetEngine()->GetModule<RenderCommanderDx11>();
    renderCommander->ReleaseResource(m_VSShader.VSPtr, ResourceType::VS);
    renderCommander->ReleaseResource(m_VSShader.LayoutPtr, ResourceType::InputLayout);
    renderCommander->ReleaseResource(m_WorldMatrix, ResourceType::Buffer);
}

void SimpleVS::UpdateShaderParams()
{

}

void SimpleVS::BindData(VisualComponent* vc)
{
    using namespace DirectX;

    Camera* camera = g_CameraHandler->GetActiveCamera();

    Mat3x3 viewMatrix = camera->GetViewMatrix();
    Mat3x3 projectionMatrix = camera->GetProjectionMatrix();
    WVP mat;

    mat.m_WMat = vc->GetOwner()->GetTransform().GetMatrix().ToXMMATRIX();
    mat.m_VMat = viewMatrix.ToXMMATRIX();
    mat.m_PMat = projectionMatrix.ToXMMATRIX();

    auto commander = Engine::GetEngine()->GetModule<RenderCommanderDx11>();

    commander->UpdateSubresouce(m_WorldMatrix, &mat, sizeof(mat));

    commander->SetConstantBuffers(&m_WorldMatrix, sizeof(ID3D11Buffer));
    commander->BindVS(&m_VSShader.VSPtr, sizeof(ID3D11VertexShader*));
    commander->SetInputLayout(&m_VSShader.LayoutPtr, sizeof(ID3D11InputLayout*));

   
}
