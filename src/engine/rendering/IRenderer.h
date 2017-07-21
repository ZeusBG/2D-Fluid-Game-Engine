#pragma once
#include "../core/IModule.h"
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

	virtual void Render() = 0;
	virtual PSHandle CreatePSFromFile(const char* file, ShaderVersion version) = 0;
	virtual VSHandle CreateVSFromFile(const char* file, ShaderVersion version) = 0;
private:
	int m_ScreenWidth;
	int m_ScreenHeight;
};

