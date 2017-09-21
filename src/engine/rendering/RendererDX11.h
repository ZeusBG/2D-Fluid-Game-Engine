#pragma once
#include "IRenderer.h"
#include "TextureManagerDX11.h"
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <queue>

class RendererDX11 : public IRenderer
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
    RendererDX11();
    virtual ~RendererDX11();

    virtual void Update(float delta);
    virtual void Init(Engine* engine);
    virtual const char* GetName();
    virtual void Destroy();

    virtual PSHandle CreatePSFromFile(const char* file, ShaderVersion version);
    virtual VSData CreateVSFromFile(const char* file, D3D11_INPUT_ELEMENT_DESC* layout, int layoutSize, ShaderVersion version);

    ID3D11Buffer* CreateConstantBuffer(UINT size);
    void ProcessCommand(RenderCommand& cmd);
	void LoadTexture(void* data, unsigned width, unsigned height, TextureFormat format, int texID);
	RenderCommand& GetLastCommand() { return m_CommandBuffer.front(); }
	void CreateDefaultSampler2D(ID3D11SamplerState** state);

    virtual ID3D11Device* GetDevice() { return m_pd3dDevice1; }

    virtual void DestroyPS(PSHandle ps);
    virtual void DestroyVS(VSData vs);

    virtual void AddRenderCommand(const RenderCommand& cmd);
    virtual void DoRenderingCommands();
	virtual void Start();

	inline TextureManagerDX11& GetTextureManager() { return m_TextureManager; }
private:
    int m_ScreenWidth;
    int m_ScreenHeight;
    HRESULT CompileShaderFromFile(const char* file, LPCSTR entryPoint, LPCSTR shaderModel, ID3DBlob** blobOut);
    HRESULT InitDevice();
    std::queue<RenderCommand> m_CommandBuffer;

	static std::pair<TextureFormat, DXGI_FORMAT> s_FormatConverter[];
	static std::pair<TextureFormat, int> s_FormatSizeConverter[];

	TextureManagerDX11 m_TextureManager;
};

using RendererDX11SP = std::shared_ptr<RendererDX11>;