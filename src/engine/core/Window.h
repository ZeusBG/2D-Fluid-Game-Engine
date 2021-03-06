#pragma once
#include <Windows.h>
#include "IModule.h"

struct WindowInfo;
struct SDL_Window;
class Window : public IModule
{
private:
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
    Window();
    ~Window();

    void Update(float delta);
    virtual void Init(Engine* engine);
    virtual const char* GetName();
    virtual void Start() {}
    HRESULT MakeWindow(const WindowInfo* info);

    virtual void Destroy();
    HINSTANCE GetHInstance() const { return m_hInst; }
    HWND GethWnd() const { return m_hWnd; }
private:
    SDL_Window* m_sdlWindow;
    HINSTANCE m_hInst = nullptr;
    HWND m_hWnd = nullptr;
    MSG m_Msg;
};

