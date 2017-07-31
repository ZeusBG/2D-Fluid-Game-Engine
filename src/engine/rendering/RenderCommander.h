#pragma once
#include "engine/core/IModule.h"
class RendererDX11;
struct ID3D11Resource;

class RenderCommanderDx11 : public IModule
{
private:
	RendererDX11* m_Renderer;
public:
	virtual void Init(Engine* engine);
	virtual void Update(float delta);
	virtual void Destroy();
	virtual const char* GetName();

	void UpdateSubresouce(ID3D11Resource* subresouce, void* data, unsigned int dataSize);
};