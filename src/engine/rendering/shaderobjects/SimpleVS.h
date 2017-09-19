#pragma once

#include "engine/rendering/IShader.h"

#include <memory>
#include <d3d11_1.h>
#include <d3dcompiler.h>


class VisualComponent;
class SimpleVS : public IShader
{
	ADD_SOLID_CLASS_METADATA(SimpleVS);
public:
    

    SimpleVS(const char* fileName) : IShader(fileName) {}
	SimpleVS() {}
    virtual void Init();
    virtual void Destroy();
    virtual void BindData(VisualComponent* vc);
    virtual void UpdateShaderParams();
private:
    VSData m_VSShader;
    ID3D11Buffer* m_WorldMatrix;
    // Add input layout
};

using SimpleVSUniquePtr = std::unique_ptr<SimpleVS, IShaderDeleter>;