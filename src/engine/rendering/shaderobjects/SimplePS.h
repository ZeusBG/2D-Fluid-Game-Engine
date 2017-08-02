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
public:
    SimplePS(const char* fileName) : IShader(fileName) {}

    virtual void Init();
    virtual void Destroy();
    virtual void BindData(ID3D11DeviceContext* context, VisualComponent* vc);
private:
	ID3D11PixelShader* m_PSShader = nullptr;
    //constant stuff
};

using SimplePSUniquePtr = std::unique_ptr<SimplePS, IShaderDeleter>;
