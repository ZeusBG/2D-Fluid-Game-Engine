#pragma once
#include "engine/core/IModule.h"
#include "engine/object/Entity.h"
#include "RenderCommand.h"
typedef void* PSHandle;
typedef void* LayoutHandle;
typedef void* VSHandle;

struct VSData
{
	VSHandle VSPtr = nullptr;
	LayoutHandle LayoutPtr = nullptr;
};


enum class ShaderVersion
{
	V4_0
};

class IRenderer : public IModule
{
public:
	virtual ~IRenderer() {}
	virtual void RenderEntities(const AVector<EntitySharedPtr>& entities) = 0;
    virtual void AddRenderCommand(const RenderCommand& cmd) = 0;
    
    // If multithreaded the thread calling this method
    // might get blocked if the rendering thread is still
    // rendering the previous frame
    virtual void DoRenderingCommands() = 0;

private:
	int m_ScreenWidth;
	int m_ScreenHeight;
};

