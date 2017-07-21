#pragma once
#include "IRenderer.h"
#include <d3d11_1.h>
#include <d3dcompiler.h>

class Renderer : public IRenderer
{
	HINSTANCE               m_hInst = nullptr;
	HWND                    m_hWnd = nullptr;
	D3D_DRIVER_TYPE         m_driverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL       m_featureLevel = D3D_FEATURE_LEVEL_11_0;
	ID3D11Device*           m_pd3dDevice = nullptr;
	ID3D11Device1*          m_pd3dDevice1 = nullptr;
	ID3D11DeviceContext*    m_pImmediateContext = nullptr;
	ID3D11DeviceContext1*   m_pImmediateContext1 = nullptr;
	IDXGISwapChain*         m_pSwapChain = nullptr;
	IDXGISwapChain1*        m_pSwapChain1 = nullptr;
	ID3D11RenderTargetView* m_pRenderTargetView = nullptr;

public:
	Renderer();
	virtual ~Renderer();

	void Render();
	virtual void Init(Engine* engine);
	virtual const char* GetName();

	virtual PSHandle CreatePSFromFile(const char* file, ShaderVersion version);
	virtual VSHandle CreateVSFromFile(const char* file, ShaderVersion version);


private:
	int m_ScreenWidth;
	int m_ScreenHeight;
	HRESULT CompileShaderFromFile(const char* file, LPCSTR entryPoint, LPCSTR shaderModel, ID3DBlob** blobOut);
	HRESULT InitDevice();
};