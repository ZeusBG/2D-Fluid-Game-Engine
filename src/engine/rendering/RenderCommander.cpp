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
	assert(dataSize < DATA_BUFFER_SIZE);
	RenderCommand cmd;
	cmd.type = RenderCmdType::UpdateSubResource;

	UpdateSubresourceData resourceData;
	resourceData.Subresource = subresouce;
	resourceData.DstSubresource = 0;
	resourceData.DstBox = nullptr;
	resourceData.SrcRowPitch = 0;
	resourceData.SrcDepthPitch = 0;
	cmd.AddStructure<UpdateSubresourceData>(resourceData, data, dataSize);

	m_Renderer->AddRenderCommand(cmd);
}

void RenderCommanderDx11::BindPS(void* shaderInfo, unsigned int shaderInfoSize)
{
	RenderCommand cmd;
	cmd.type = RenderCmdType::BindPS;
	memcpy(cmd.CommandData, shaderInfo, shaderInfoSize);

	m_Renderer->AddRenderCommand(cmd);
}

void RenderCommanderDx11::BindVS(void* shaderInfo, unsigned int shaderInfoSize)
{
	RenderCommand cmd;
	cmd.type = RenderCmdType::BindVS;
	memcpy(cmd.CommandData, shaderInfo, shaderInfoSize);

	m_Renderer->AddRenderCommand(cmd);
}

void RenderCommanderDx11::SetInputLayout(void* layout, unsigned int dataSize)
{
	RenderCommand cmd;
	cmd.type = RenderCmdType::SetInputLayout;
	memcpy(cmd.CommandData, layout, dataSize);

	m_Renderer->AddRenderCommand(cmd);
}

void RenderCommanderDx11::SetConstantBuffers(ID3D11Buffer** buffer, unsigned int dataSize)
{
	RenderCommand cmd;
	cmd.type = RenderCmdType::SetConstantBuffers;
	memcpy(cmd.CommandData, &buffer, sizeof(ID3D11Buffer**));

	m_Renderer->AddRenderCommand(cmd);
}

void RenderCommanderDx11::SetVertexBuffers(ID3D11Buffer* const* buffer, unsigned int stride, unsigned int offset)
{
	RenderCommand cmd;
	cmd.type = RenderCmdType::SetVertexBuffers;

	VertexBufferInfo info{buffer, stride, offset};
	cmd.AddStructure<VertexBufferInfo>(info, nullptr, 0);

	m_Renderer->AddRenderCommand(cmd);
}

void RenderCommanderDx11::SetTopology(Topology topology)
{
	RenderCommand cmd;
	cmd.type = RenderCmdType::SetTopology;
	memcpy(cmd.CommandData, &topology, sizeof(Topology));

	m_Renderer->AddRenderCommand(cmd);
}

void RenderCommanderDx11::DrawIndexed(unsigned int indexCount, unsigned int startIndex, unsigned int baseVertexlocation)
{
	RenderCommand cmd;
	cmd.type = RenderCmdType::DrawIndexed;

	DrawIndexedInfo info{ indexCount, startIndex, baseVertexlocation };
	cmd.AddStructure<DrawIndexedInfo>(info, nullptr, 0);

	m_Renderer->AddRenderCommand(cmd);
}

void RenderCommanderDx11::CreateBuffer(const D3D11_BUFFER_DESC& Desc, D3D11_SUBRESOURCE_DATA* InitialData, ID3D11Buffer** Buffer)
{
	RenderCommand cmd;
	cmd.type = RenderCmdType::CreateBuffer;

	CreateBufferInfo info;
	info.Desc = Desc;
	info.InitialData = InitialData;
	info.Buffer = Buffer;
	cmd.AddStructure<CreateBufferInfo>(info, InitialData, sizeof(D3D11_SUBRESOURCE_DATA));

	m_Renderer->AddRenderCommand(cmd);
}

void RenderCommanderDx11::ReleaseResource(void* resourcePtr, ResourceType type)
{
    RenderCommand cmd;
    cmd.type = RenderCmdType::ReleaseResource;

    RelaseResourceInfo info;
    info.Ptr = resourcePtr;
    info.Type = type;
    cmd.AddStructure<RelaseResourceInfo>(info);

    m_Renderer->AddRenderCommand(cmd);
}

void RenderCommanderDx11::CreateTexture(uint8_t* data, uint32_t width, uint32_t height, TextureFormat format, int texID)
{
	RenderCommand cmd;
	cmd.type = RenderCmdType::CreateTex;

	CreateTextureInfo createTextureInfo;
	createTextureInfo.data = data;
	createTextureInfo.Width = width;
	createTextureInfo.Height = height;
	createTextureInfo.Format = format;
	createTextureInfo.TexID = texID;
	cmd.AddStructure<CreateTextureInfo>(createTextureInfo);

	m_Renderer->AddRenderCommand(cmd);

}

void RenderCommanderDx11::BindTexture(int textureID)
{
	RenderCommand cmd;
	cmd.type = RenderCmdType::BindTex;

	BindTextureInfo bindTextureInfo;
	bindTextureInfo.TextureID = textureID;
	cmd.AddStructure<BindTextureInfo>(bindTextureInfo);
	
	m_Renderer->AddRenderCommand(cmd);
}

void RenderCommanderDx11::DeleteTexture(int textureID)
{
	RenderCommand cmd;
	cmd.type = RenderCmdType::ReleaseTexture;
	cmd.AddStructure(textureID);

	m_Renderer->AddRenderCommand(cmd);
}

void RenderCommanderDx11::CreateSampler2D(ID3D11SamplerState** state)
{
	RenderCommand cmd;
	cmd.type = CreateSampler2DCmd;

	memcpy(cmd.CommandData, &state, sizeof(ID3D11SamplerState**));

	m_Renderer->AddRenderCommand(cmd);
}

void RenderCommanderDx11::SetSampler2D(ID3D11SamplerState ** state)
{
	RenderCommand cmd;
	cmd.type = SetSampler2DCmd;

	memcpy(cmd.CommandData, &state, sizeof(ID3D11SamplerState**));

	m_Renderer->AddRenderCommand(cmd);
}

void RenderCommanderDx11::SetIndexBuffers(ID3D11Buffer* indexBuffer, DataSizeFormat format, unsigned int offset)
{
	RenderCommand cmd;
	cmd.type = RenderCmdType::SetIndexBuffer;

	IndexBufferInfo info{ indexBuffer, format, offset };
	cmd.AddStructure<IndexBufferInfo>(info, nullptr, 0);

	m_Renderer->AddRenderCommand(cmd);
}