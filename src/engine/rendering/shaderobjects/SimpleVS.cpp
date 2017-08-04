#pragma once

#include "engine/core/Engine.h"
#include "engine/rendering/shaderobjects/SimpleVS.h"
#include "engine/rendering/RendererDX11.h"
#include "engine/object/VisualComponent.h"
#include "util/math/MathUtils.h"
#include "engine/rendering/RenderCommander.h"

#include <d3d11_1.h>
#include <d3dcompiler.h>

void SimpleVS::Init()
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
    m_VSShader = renderer->CreateVSFromFile(m_FileName.c_str(), layout, numElements, ShaderVersion::V4_0);
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(DirectX::XMMATRIX);
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bd.CPUAccessFlags = 0;
    renderer->GetDevice()->CreateBuffer(&bd, nullptr, &m_WorldMatrix);
    auto renderCommander = Engine::GetEngine()->GetModule<RenderCommanderDx11>();
    renderCommander->CreateBuffer(&bd, nullptr, &m_WorldMatrix);
}

void SimpleVS::Destroy()
{
    auto renderer = Engine::GetEngine()->GetModule<RendererDX11>();
    Engine::GetEngine()->GetModule<RendererDX11>()->DestroyVS(m_VSShader);
}

void SimpleVS::UpdateShaderParams()
{

}

void SimpleVS::BindData(VisualComponent* vc)
{
    using namespace DirectX;

    XMMATRIX test = vc->GetOwner()->GetTransform().GetMatrix().ToXMMATRIX();
    auto commander = Engine::GetEngine()->GetModule<RenderCommanderDx11>();
    commander->UpdateSubresouce(m_WorldMatrix, &test, sizeof(test));
    commander->SetConstantBuffers(&m_WorldMatrix, sizeof(ID3D11Buffer));
    commander->BindVS(&m_VSShader.VSPtr, sizeof(ID3D11VertexShader*));
    commander->SetInputLayout(&m_VSShader.LayoutPtr, sizeof(ID3D11InputLayout*));
}
