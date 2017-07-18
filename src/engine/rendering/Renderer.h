#pragma once
#include "IRenderer.h"

class Renderer : public IRenderer
{
public:
	Renderer();
	virtual ~Renderer();

	void Render();
	virtual void Init(Engine* engine);
	virtual const char* GetName();
private:
	int m_ScreenWidth;
	int m_ScreenHeight;
};

