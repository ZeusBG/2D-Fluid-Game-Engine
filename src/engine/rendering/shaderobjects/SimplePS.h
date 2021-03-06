#pragma once

#include "engine/rendering/IRenderer.h"
#include "engine/rendering/IShader.h"

#include <memory>
#include <d3d11_1.h>
#include <d3dcompiler.h>

class VisualComponent;
struct ID3D11PixelShader;
class SimplePS : public IShader
{
	// TODO Later when there is a shader factory
	// change the create function !!
	ADD_SOLID_CLASS_METADATA(SimplePS);
public:
    SimplePS(const char* fileName) : IShader(fileName) {}
	SimplePS() {}
    virtual void Init();
    virtual void Destroy();
    virtual void BindData(VisualComponent* vc);
private:
    ID3D11PixelShader* m_PSShader = nullptr;
    //constant stuff
};

using SimplePSUniquePtr = std::unique_ptr<SimplePS, IShaderDeleter>;
