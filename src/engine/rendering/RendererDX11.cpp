#pragma once
#include "RendererDX11.h"
#include "../core/SystemSettings.h"
#include "../core/Engine.h"
#include <d3dcompiler.h>
#include <directxmath.h>
#include "../../util/StringUtils.h"


RendererDX11::RendererDX11() {}
RendererDX11::~RendererDX11() {}
using namespace DirectX;

void RendererDX11::Init(Engine* engine)
{
    const SystemSettings* settings = engine->GetSettings();
    m_ScreenWidth = settings->ScreenWidth;
    m_ScreenHeight = settings->ScreenHeight;
    
    const Window* window = engine->GetModule<Window>();
    m_hWnd = window->GethWnd();
    m_hInst = window->GetHInstance();

    InitDevice();
}

HRESULT RendererDX11::InitDevice()
{
    HRESULT hr = S_OK;

    RECT rc;
    GetClientRect(m_hWnd, &rc);
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;

    UINT createDeviceFlags = 0;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
    };
    UINT numDriverTypes = ARRAYSIZE(driverTypes);

    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };
    UINT numFeatureLevels = ARRAYSIZE(featureLevels);

    for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
    {
        m_driverType = driverTypes[driverTypeIndex];
        hr = D3D11CreateDevice(nullptr, m_driverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels,
            D3D11_SDK_VERSION, &m_pd3dDevice, &m_featureLevel, &m_pImmediateContext);

        if (hr == E_INVALIDARG)
        {
            // DirectX 11.0 platforms will not recognize D3D_FEATURE_LEVEL_11_1 so we need to retry without it
            hr = D3D11CreateDevice(nullptr, m_driverType, nullptr, createDeviceFlags, &featureLevels[1], numFeatureLevels - 1,
                D3D11_SDK_VERSION, &m_pd3dDevice, &m_featureLevel, &m_pImmediateContext);
        }

        if (SUCCEEDED(hr))
            break;
    }
    if (FAILED(hr))
        return hr;

    // Obtain DXGI factory from device (since we used nullptr for pAdapter above)
    IDXGIFactory1* dxgiFactory = nullptr;
    {
        IDXGIDevice* dxgiDevice = nullptr;
        hr = m_pd3dDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice));
        if (SUCCEEDED(hr))
        {
            IDXGIAdapter* adapter = nullptr;
            hr = dxgiDevice->GetAdapter(&adapter);
            if (SUCCEEDED(hr))
            {
                hr = adapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&dxgiFactory));
                adapter->Release();
            }
            dxgiDevice->Release();
        }
    }
    if (FAILED(hr))
        return hr;

    // Create swap chain
    IDXGIFactory2* dxgiFactory2 = nullptr;
    hr = dxgiFactory->QueryInterface(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(&dxgiFactory2));
    if (dxgiFactory2)
    {
        // DirectX 11.1 or later
        hr = m_pd3dDevice->QueryInterface(__uuidof(ID3D11Device1), reinterpret_cast<void**>(&m_pd3dDevice1));
        if (SUCCEEDED(hr))
        {
            (void)m_pImmediateContext->QueryInterface(__uuidof(ID3D11DeviceContext1), reinterpret_cast<void**>(&m_pImmediateContext1));
        }

        DXGI_SWAP_CHAIN_DESC1 sd;
        ZeroMemory(&sd, sizeof(sd));
        sd.Width = width;
        sd.Height = height;
        sd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.BufferCount = 1;

        hr = dxgiFactory2->CreateSwapChainForHwnd(m_pd3dDevice, m_hWnd, &sd, nullptr, nullptr, &m_pSwapChain1);
        if (SUCCEEDED(hr))
        {
            hr = m_pSwapChain1->QueryInterface(__uuidof(IDXGISwapChain), reinterpret_cast<void**>(&m_pSwapChain));
        }

        dxgiFactory2->Release();
    }
    else
    {
        // DirectX 11.0 systems
        DXGI_SWAP_CHAIN_DESC sd;
        ZeroMemory(&sd, sizeof(sd));
        sd.BufferCount = 1;
        sd.BufferDesc.Width = width;
        sd.BufferDesc.Height = height;
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferDesc.RefreshRate.Numerator = 60;
        sd.BufferDesc.RefreshRate.Denominator = 1;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.OutputWindow = m_hWnd;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.Windowed = TRUE;

        hr = dxgiFactory->CreateSwapChain(m_pd3dDevice, &sd, &m_pSwapChain);
    }
    dxgiFactory->MakeWindowAssociation(m_hWnd, DXGI_MWA_NO_ALT_ENTER);

    dxgiFactory->Release();

    if (FAILED(hr))
        return hr;

    // Create a render target view
    ID3D11Texture2D* pBackBuffer = nullptr;
    hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
    if (FAILED(hr))
        return hr;

    hr = m_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &m_pRenderTargetView);
    pBackBuffer->Release();
    if (FAILED(hr))
        return hr;

    m_pImmediateContext->OMSetRenderTargets(1, &m_pRenderTargetView, nullptr);

    // Setup the viewport
    D3D11_VIEWPORT vp;
    vp.Width = (FLOAT)width;
    vp.Height = (FLOAT)height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    m_pImmediateContext->RSSetViewports(1, &vp);

    return S_OK;
}

void RendererDX11::Update(float delta)
{

    //TODO istoilov : finish this;
    // set our new render target object as the active render target
    m_pImmediateContext1->OMSetRenderTargets(1, &m_pRenderTargetView, nullptr);

    // clear the back buffer to a deep blue
    float color[4] = { 0.0f, 0.2f, 0.4f, 1.0f };
    m_pImmediateContext1->ClearRenderTargetView(m_pRenderTargetView, color);

    // set the vertex buffer
    //UINT stride = sizeof(VERTEX);
    //UINT offset = 0;
    //devcon->IASetVertexBuffers(0, 1, vertexbuffer.GetAddressOf(), &stride, &offset);

    // set the primitive topology
    m_pImmediateContext1->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // draw 3 vertices, starting from vertex 0
    //devconm_pImmediateContext1->Draw(3, 0);

    // switch the back buffer and the front buffer
    m_pSwapChain1->Present(1, 0);
}

HRESULT RendererDX11::CompileShaderFromFile(const char* file, LPCSTR entryPoint, LPCSTR shaderModel, ID3DBlob** blobOut)
{
    std::wstring fileName = StrToWstr(file);
    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef DEBUG
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;

    // Disable optimizations to further improve shader debugging
    dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

    ID3DBlob* pErrorBlob = nullptr;
    hr = D3DCompileFromFile(fileName.c_str(), nullptr, nullptr, entryPoint, shaderModel,
        dwShaderFlags, 0, blobOut, &pErrorBlob);
    if (FAILED(hr))
    {
        if (pErrorBlob)
        {
            OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
            pErrorBlob->Release();
        }
        return hr;
    }
    if (pErrorBlob) pErrorBlob->Release();

    return S_OK;
}

PSHandle RendererDX11::CreatePSFromFile(const char* file, ShaderVersion version)
{
    std::string shaderVersion;
    //TODO this is dumb way of converting shader vesion to string
    switch (version)
    {
    case ShaderVersion::V4_0:
        shaderVersion = "ps_4_0";
        break;
    }

    ID3DBlob* pPSBlob = nullptr;
    HRESULT hr = this->CompileShaderFromFile(file, "PS", shaderVersion.c_str(), &pPSBlob);
    if (FAILED(hr))
    {
        //TODO replace with logger when we have logger implemented
        MessageBox(nullptr,
            L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
        return nullptr;
    }

    // Create the pixel shader
    ID3D11PixelShader* PixelShader = nullptr;
    hr = m_pd3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &PixelShader);
    pPSBlob->Release();
    if (FAILED(hr))
        return nullptr;
    return static_cast<void*>(PixelShader);
}

VSHandle RendererDX11::CreateVSFromFile(const char* file, ShaderVersion version)
{
    std::string shaderVersion;
    //TODO this is dumb way of converting shader vesion to string
    switch (version)
    {
    case ShaderVersion::V4_0:
        shaderVersion = "vs_4_0";
        break;
    }

    ID3DBlob* pPSBlob = nullptr;
    HRESULT hr = this->CompileShaderFromFile(file, "VS", shaderVersion.c_str(), &pPSBlob);
    if (FAILED(hr))
    {
        //TODO replace with logger when we have logger implemented
        MessageBox(nullptr,
            L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
        return nullptr;
    }

    // Create the pixel shader
    ID3D11VertexShader* VertexShader = nullptr;
    hr = m_pd3dDevice->CreateVertexShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &VertexShader);
    pPSBlob->Release();
    if (FAILED(hr))
        return nullptr;
    return static_cast<void*>(VertexShader);
}

const char* RendererDX11::GetName() { return "Renderer"; }

void RendererDX11::Destroy()
{
    if (m_pImmediateContext) m_pImmediateContext->ClearState();
    if (m_pRenderTargetView) m_pRenderTargetView->Release();
    if (m_pSwapChain1) m_pSwapChain1->Release();
    if (m_pSwapChain) m_pSwapChain->Release();
    if (m_pImmediateContext1) m_pImmediateContext1->Release();
    if (m_pImmediateContext) m_pImmediateContext->Release();
    if (m_pd3dDevice1) m_pd3dDevice1->Release();
    if (m_pd3dDevice) m_pd3dDevice->Release();
}
