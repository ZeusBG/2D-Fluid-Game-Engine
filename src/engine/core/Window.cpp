#pragma once
#include "Window.h"
#include "IModule.h"
#include "Engine.h"
#include "SystemSettings.h"
#include "engine/input/InputHandler.h"

#include "SDL.h"
#include "SDL_syswm.h"

Window::Window() {}

void Window::Init(Engine* engine)
{
    MakeWindow(&engine->GetSettings()->WindowInfo);
}

HRESULT Window::MakeWindow(const WindowInfo* info)
{
    m_hInst = info->hInstance;
    m_lpCmdLine = info->lpCmdLine;
    m_nCmdShow = info->nCmdShow;
    // Register class
    /*WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = info->hInstance;
    wcex.hIcon = nullptr;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = L"2D Game Engine";
    wcex.hIconSm = nullptr;
    if (!RegisterClassEx(&wcex))
        return E_FAIL;*/

    // Create window

    SDL_Init(SDL_INIT_VIDEO);

    m_sdlWindow = SDL_CreateWindow("2D Game Engine", 300, 300, 800, 600, 0);
    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    SDL_GetWindowWMInfo(m_sdlWindow, &wmInfo);
    m_hWnd = wmInfo.info.win.window;

    /*RECT rc = { 0, 0, 800, 600 };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
    m_hWnd = CreateWindow(L"2D Game Engine", L"Pre-Alpha",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, info->hInstance,
        nullptr);
    if (!m_hWnd)
        return E_FAIL;*/

    ShowWindow(m_hWnd, info->nCmdShow);

    return S_OK;
}

void Window::Destroy()
{

    SDL_VideoQuit();
    SDL_DestroyWindow(m_sdlWindow);
    SDL_Quit();
}

LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    switch (message)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        break;
    
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default: return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void Window::Update(float delta)
{
    while (PeekMessage(&m_Msg, nullptr, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&m_Msg);
        DispatchMessage(&m_Msg);
        if (WM_QUIT == m_Msg.message || g_Engine->GetModule<InputHandler>()->QuitRequested())
        {
            Engine::GetEngine()->Stop();
        }
    }
}

const char* Window::GetName() { return "Window"; }
Window::~Window() {}

