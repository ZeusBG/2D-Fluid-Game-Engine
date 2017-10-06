#pragma once
#include "IMesh.h"
#include "engine/core/Engine.h"
#include "engine/rendering/RenderCommander.h"
#include <d3d11.h>

void IMesh::CreateBuffer(const D3D11_BUFFER_DESC& desc, ID3D11Buffer** buffer, void* initialData)
{
	D3D11_SUBRESOURCE_DATA bufferData;
	ZeroMemory(&bufferData, sizeof(bufferData));

	bufferData.pSysMem = initialData;

	auto renderCommander = g_Engine->GetModule<RenderCommanderDx11>();
	renderCommander->CreateBuffer(desc, &bufferData, buffer);
}

void IMesh::ReleaseBuffer(ID3D11Buffer** buffer)
{
	// Release the index buffer.
	assert(buffer);
    if (buffer)
    {
		(*buffer)->Release();
    }
}