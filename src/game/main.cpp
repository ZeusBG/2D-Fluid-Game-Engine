#pragma once
#include <windows.h>
#include "GameClient.h"


int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	GameClient client;
	WindowInfo info;
	info.hInstance = hInstance;
	info.hPrevInstance = hPrevInstance;
	info.lpCmdLine = lpCmdLine;
	info.nCmdShow = nCmdShow;
	SystemSettings settings;

	settings.ScreenWidth = 800;
	settings.ScreenHeight = 600;
	settings.WindowInfo = info;

	client.Init(settings);
	client.Start();
	return 0;
}