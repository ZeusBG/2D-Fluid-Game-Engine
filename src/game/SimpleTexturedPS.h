#pragma once
#include "engine/rendering/shaderobjects/SimplePS.h"

#include <memory>
#include <d3d11_1.h>
#include <d3dcompiler.h>

class VisualComponent;
struct ID3D11PixelShader;
class SimpleTexturedPS : public SimplePS
{
	// TODO Later when there is a shader factory
	// change the create function !!
	ADD_SOLID_CLASS_METADATA(SimplePS);
public:
	SimpleTexturedPS(const char* fileName) : SimplePS(fileName) {}
	SimpleTexturedPS() {}
    virtual void Init();
    virtual void Destroy();
    virtual void BindData(VisualComponent* vc);
private:
	ID3D11SamplerState* m_sampleState;
};

using SimplePSUniquePtr = std::unique_ptr<SimplePS, IShaderDeleter>;
