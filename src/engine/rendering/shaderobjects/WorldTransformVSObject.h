#pragma once

#include "engine/rendering/IShader.h"
#include "util/Math.h"

#include <d3d11_1.h>
#include <directXMath.h>
#include <memory>

using namespace DirectX;

class WorldTransformVSObject : public IShader
{
private:
    struct MatrixBufferType
    {
        XMMATRIX world;
        /*D3DXMATRIX view;
        D3DXMATRIX projection;*/
    };

public:

    WorldTransformVSObject(const char* fileName) : IShader(fileName) {}

    virtual void Init();
    virtual void Destroy();
    virtual void BindData(ID3D11DeviceContext* context);

    virtual void UpdateShaderParams(ID3D11DeviceContext* deviceContext, const Mat3x3& worldMatrix);

private:
    VSData m_VSData;

    ID3D11Buffer* m_MatrixBuffer;
};