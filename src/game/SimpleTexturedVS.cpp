#pragma once
#include "SimpleTexturedVS.h"
#include "engine/core/Engine.h"
#include "engine/rendering/RendererDX11.h"
IMPLEMENT_METADATA(SimpleTexturedVS);

void SimpleTexturedVS::Init()
{
	auto renderer = g_Engine->GetModule<RendererDX11>();
	if (!renderer)
	{
		//TODO add log messsage after logger is merged
		return;
	}
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE(layout);
	m_VSShader = renderer->CreateVSFromFile(m_FileName.c_str(), layout, numElements, ShaderVersion::V4_0);

	InitConstantBuffers();
}
