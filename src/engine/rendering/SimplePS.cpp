#pragma once
#include "RendererDX11.h"
#include "../core/Engine.h"
#include "SimplePS.h"

#include <d3d11_1.h>
#include <d3dcompiler.h>

void SimplePS::Init()
{
	RendererDX11* renderer = Engine::GetEngine()->GetModule<RendererDX11>();
	if (!renderer)
	{
		//TODO add log messsage after logger is merged
		return;
	}
	m_PSShader = renderer->CreatePSFromFile(m_FileName.c_str(), ShaderVersion::V4_0);
}

void SimplePS::Destroy()
{
	Engine::GetEngine()->GetModule<RendererDX11>()->DestroyPS(m_PSShader);
}

void SimplePS::BindData(ID3D11DeviceContext* context)
{
	context->PSSetShader(static_cast<ID3D11PixelShader*>(m_PSShader), nullptr, 0);
}
