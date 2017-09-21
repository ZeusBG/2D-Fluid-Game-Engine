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
    virtual void Init() override;
    virtual void Destroy() override;
    virtual void BindData(VisualComponent* vc) override;
    virtual void UpdateShaderParams() override;
	virtual void InitConstantBuffers() override;
protected:
    VSData m_VSShader;
    ID3D11Buffer* m_WorldMatrix;
    // Add input layout
};

using SimpleVSUniquePtr = std::unique_ptr<SimpleVS, IShaderDeleter>;