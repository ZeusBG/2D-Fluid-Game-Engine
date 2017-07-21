#pragma once
#include "Window.h"
#include "IModule.h"
#include "Engine.h"
#include "SystemSettings.h"
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
	WNDCLASSEX wcex;
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
	wcex.lpszClassName = L"TutorialWindowClass";
	wcex.hIconSm = nullptr;
	if (!RegisterClassEx(&wcex))
		return E_FAIL;

	// Create window

	RECT rc = { 0, 0, 800, 600 };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	m_hWnd = CreateWindow(L"TutorialWindowClass", L"Direct3D 11 Tutorial 3: Shaders",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, info->hInstance,
		nullptr);
	if (!m_hWnd)
		return E_FAIL;

	ShowWindow(m_hWnd, info->nCmdShow);

	return S_OK;
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
	
		// Note that this tutorial does not handle resizing (WM_SIZE) requests,
		// so we created the window without the resize border.
	
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void Window::Update()
{
	while (PeekMessage(&m_Msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&m_Msg);
		DispatchMessage(&m_Msg);
		if (WM_QUIT == m_Msg.message)
		{
			DeInit();
		}
	}
}

void Window::DeInit()
{
	Engine::GetEngine()->Stop();
}

const char* Window::GetName() { return "Window"; }
Window::~Window() {}

