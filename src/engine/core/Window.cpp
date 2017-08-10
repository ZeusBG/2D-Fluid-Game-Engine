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

    SDL_Init(SDL_INIT_VIDEO);

    m_sdlWindow = SDL_CreateWindow("2D Game Engine", 300, 300, 800, 600, 0);
    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    SDL_GetWindowWMInfo(m_sdlWindow, &wmInfo);
    m_hWnd = wmInfo.info.win.window;

    ShowWindow(m_hWnd, info->nCmdShow);

    return S_OK;
}

void Window::Destroy()
{
    SDL_VideoQuit();
    SDL_DestroyWindow(m_sdlWindow);
    SDL_Quit();
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

