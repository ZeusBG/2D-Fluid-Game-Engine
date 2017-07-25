#pragma once
#include <Windows.h>
#include "IModule.h"

struct WindowInfo;

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

	HRESULT MakeWindow(const WindowInfo* info);

	virtual void Destroy();
	HINSTANCE GetHInstance() const { return m_hInst; }
	HWND GethWnd() const { return m_hWnd; }
private:
	HINSTANCE m_hInst = nullptr;
	HWND m_hWnd = nullptr;
	LPWSTR m_lpCmdLine;
	int m_nCmdShow;
	MSG m_Msg;
};

