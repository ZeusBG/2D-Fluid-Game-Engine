#pragma once
#include <cstring>
#include <d3d11.h>

#define STRUCTURE_SIZE 256
#define DATA_BUFFER_SIZE 1024

enum RenderCmdType
{
	CreateBuffer,
	SetVS,
	SetPS,
	UpdateSubResource,
	BindVS,
	BindPS,
	SetVertexBuffers,
	SetIndexBuffer,
	SetTopology,
	SetInputLayout,
	SetConstantBuffers,
	DrawIndexed
};

struct DrawIndexedInfo
{
	unsigned int IndexCount;
	unsigned int StartIndex;
	unsigned int BaseVertexlocation;
};

struct VertexBufferInfo
{
	ID3D11Buffer* const* VB;
	unsigned int Stride;
	unsigned int Offset;
};

enum DataSizeFormat
{
	R32_UINT
};

enum Topology
{
	TRIANGLE_LIST
};

struct CreateBufferInfo
{
	D3D11_BUFFER_DESC Desc;
	D3D11_SUBRESOURCE_DATA* InitialData;
	ID3D11Buffer** Buffer;
};

struct IndexBufferInfo
{
	ID3D11Buffer* IB;
	DataSizeFormat Format;
	unsigned int Offset;
};

struct UpdateSubresourceData
{
	ID3D11Resource* Subresource;
	unsigned int DstSubresource;
	D3D11_BOX* DstBox;
	void* Data;
	unsigned int SrcRowPitch;
	unsigned int SrcDepthPitch;
};

struct RenderCommand
{
    RenderCmdType type;
    char CommandStructure[STRUCTURE_SIZE];
	char CommandData[DATA_BUFFER_SIZE];

	RenderCommand() {}

	RenderCommand(const RenderCommand& other)
	{
		type = other.type;
		memcpy(CommandStructure, other.CommandStructure, STRUCTURE_SIZE);
		memcpy(CommandData, other.CommandData, DATA_BUFFER_SIZE);
	}

	RenderCommand& operator=(const RenderCommand& other)
	{
		if (this == &other)
			return *this;
		type = other.type;
		memcpy(CommandStructure, other.CommandStructure, STRUCTURE_SIZE);
		memcpy(CommandData, other.CommandData, DATA_BUFFER_SIZE);
		return *this;
	}

	template <typename T>
	void AddStructure(const T& structure, void* userData = nullptr, unsigned int dataSize = 0)
	{
		memcpy(CommandStructure, &structure, sizeof(T));

		if (userData)
		{
			memcpy(CommandData, userData, dataSize);
		}
	}
};