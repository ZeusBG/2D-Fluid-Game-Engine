#pragma once

struct WindowInfo
{
	HINSTANCE hInstance;
	HINSTANCE hPrevInstance;
	LPWSTR lpCmdLine;
	int nCmdShow;
};

struct SystemSettings
{
	int ScreenWidth;
	int ScreenHeight;
	WindowInfo WindowInfo;
};

