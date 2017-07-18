#pragma once

class SystemSettings
{
private:
	int m_ScreenWidth;
	int m_ScreenHeight;
public:
	int GetScreenWidth() const { return m_ScreenWidth; }
	int GetScreenHeight() const { return m_ScreenHeight; }
	void SetScreenWidth(int width) { m_ScreenWidth = width; }
	void SetScreenHeight(int height) { m_ScreenHeight = height; }
};

