#pragma once
#include <cstring>

struct ID3D11Resource;
struct D3D11_BOX;

#define STRUCTURE_SIZE 256
#define DATA_BUFFER_SIZE 1024

enum RenderCmdType
{
    SetVS,
    SetPS,
    UpdateSubResource,
    BindVS,
    BindPS,
    SetVertexBuffers,
    SetIndexBuffer,
    SetTopology,
    SetInputLayout,
    SetConstantBuffers
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

struct PtrData
{
    void* ptr;
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
	void AddStructure(const T& structure, void* userData, unsigned int dataSize)
	{
		memcpy(CommandStructure, &structure, sizeof(structure));

		if (userData)
		{
			memcpy(CommandData, userData, dataSize);
		}
	}
};