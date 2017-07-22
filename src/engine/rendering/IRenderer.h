#pragma once
#include "engine/core/IModule.h"

typedef void* PSHandle;
typedef void* VSHandle;

enum class ShaderVersion
{
	V4_0
};

class IRenderer : public IModule
{
public:
	virtual ~IRenderer() {}

	virtual PSHandle CreatePSFromFile(const char* file, ShaderVersion version) = 0;
	virtual VSHandle CreateVSFromFile(const char* file, ShaderVersion version) = 0;

	virtual void DestroyPS(PSHandle ps) = 0;
	virtual void DestroyVS(VSHandle vs) = 0;

private:
	int m_ScreenWidth;
	int m_ScreenHeight;
};

