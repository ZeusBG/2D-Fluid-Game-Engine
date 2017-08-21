#pragma once
#include <Windows.h>

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

