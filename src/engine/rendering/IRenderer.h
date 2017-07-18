#pragma once
#include "../Interface.h"

class IRenderer : public Interface
{
public:
	virtual ~IRenderer() {}

	virtual void Render() = 0;
private:
	int m_ScreenWidth;
	int m_ScreenHeight;
};

