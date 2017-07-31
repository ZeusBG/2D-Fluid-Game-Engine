#pragma once
#include "RenderCommander.h"
#include "RenderCommand.h"
#include "RendererDX11.h"
#include "engine/core/Engine.h"
#include <cstring>
#include <DirectXMath.h>
void RenderCommanderDx11::Init(Engine * engine)
{
	m_Renderer = engine->GetModule<RendererDX11>();
}
void RenderCommanderDx11::Update(float delta)
{
}
void RenderCommanderDx11::Destroy()
{
}
const char* RenderCommanderDx11::GetName()
{
	return "RenderCommanderDx11";
}
void RenderCommanderDx11::UpdateSubresouce(ID3D11Resource* subresouce, void* data, unsigned int dataSize)
{
	RenderCommand cmd;
	cmd.type = RenderCmdType::UpdateSubResource;

	UpdateSubresourceData resourceData;
	resourceData.Subresource = subresouce;
	resourceData.DstSubresource = 0;
	resourceData.DstBox = nullptr;
	resourceData.SrcRowPitch = 0;
	resourceData.SrcDepthPitch = 0;

	cmd.AddStructure(resourceData, data, dataSize);

	m_Renderer->AddRenderCommand(cmd);

}
