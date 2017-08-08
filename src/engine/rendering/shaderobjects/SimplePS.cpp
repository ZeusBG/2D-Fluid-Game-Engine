#pragma once
#include "engine/rendering/RendererDX11.h"
#include "engine/core/Engine.h"
#include "engine/rendering/shaderobjects/SimplePS.h"
#include "../RenderCommander.h"

#include <d3d11_1.h>
#include <d3dcompiler.h>

void SimplePS::Init()
{
    auto renderer = Engine::GetEngine()->GetModule<RendererDX11>();
	if (!renderer)
	{
		//TODO add log messsage after logger is merged
		return;
	}
	m_PSShader = (ID3D11PixelShader*)renderer->CreatePSFromFile(m_FileName.c_str(), ShaderVersion::V4_0);
}

void SimplePS::Destroy()
{
	Engine::GetEngine()->GetModule<RendererDX11>()->DestroyPS(m_PSShader);
}

void SimplePS::BindData(VisualComponent* vc)
{
	auto renderCommander = Engine::GetEngine()->GetModule<RenderCommanderDx11>();
	renderCommander->BindPS(&m_PSShader, sizeof(ID3D11PixelShader*));
}