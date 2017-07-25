#pragma once

#include "engine/rendering/IShader.h"

#include <memory>
#include <d3d11_1.h>
#include <d3dcompiler.h>

class VisualComponent;
class SimpleVS : public IShader
{
public:
    SimpleVS(const char* fileName) : IShader(fileName) {}

    virtual void Init();
    virtual void Destroy();
    virtual void BindData(ID3D11DeviceContext* context);
private:
    VSData m_VSShader;
    // Add input layout
};

using SimpleVSUniquePtr = std::unique_ptr<SimpleVS, IShaderDeleter>;