#pragma once
#include "engine/core/IModule.h"
#include "RenderCommand.h"
class RendererDX11;
struct ID3D11Resource;
struct ID3D11VertexShader;
struct ID3D11Buffer;
struct ID3D11InputLayout;

class RenderCommanderDx11 : public IModule
{
private:
	RendererDX11* m_Renderer;
public:
	virtual void Init(Engine* engine);
	virtual void Update(float delta);
	virtual void Destroy();
	virtual const char* GetName();
	virtual void Start() {}

	void UpdateSubresouce(ID3D11Resource* subresouce, void* data, unsigned int dataSize);
	void BindPS(void* ShaderPtr, unsigned int shaderInfoSize);
	void BindVS(void* ShaderPtr, unsigned int shaderInfoSize);
	void SetInputLayout(void* layout, unsigned int dataSize);
	void SetConstantBuffers(ID3D11Buffer** buffer, unsigned int dataSize);
	void SetVertexBuffers(ID3D11Buffer* const* buffer, unsigned int stride, unsigned int offset);
	void SetIndexBuffers(ID3D11Buffer* indexBuffer, DataSizeFormat format, unsigned int offset);
	void SetTopology(Topology topology);
	void DrawIndexed(unsigned int indexCount, unsigned int startIndex, unsigned int baseVertexlocation);
	void CreateBuffer(D3D11_BUFFER_DESC* Desc, D3D11_SUBRESOURCE_DATA* InitialData, ID3D11Buffer** Buffer);
};