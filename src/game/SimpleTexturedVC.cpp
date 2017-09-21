#include "SimpleTexturedVC.h"
#include "engine/rendering/IShader.h"
#include "engine/core/Engine.h"
#include "engine/rendering/RenderCommander.h"
#include "engine/rendering/RendererDX11.h"
#include "game/SimpleTexturedPS.h"
#include "game/SimpleTexturedVS.h"
#include <memory>
IMPLEMENT_METADATA(SimpleTexturedVC)

SimpleTexturedVC::SimpleTexturedVC()
{
	m_PixelShader = std::static_pointer_cast<IShader>(IShader::ShaderSharedPtr<SimpleTexturedPS>("resources/shaders/SimpleTexturePS.hlsl"));
	m_VertexShader = std::static_pointer_cast<IShader>(IShader::ShaderSharedPtr<SimpleTexturedVS>("resources/shaders/SimpleTextureVS.hlsl"));
}

void SimpleTexturedVC::Update(float dt)
{
	g_Engine->GetModule<RenderCommanderDx11>()->BindTexture(m_TextureID);
	SimpleVisualComponent::Update(dt);
}

void SimpleTexturedVC::Init()
{
	SimpleVisualComponent::Init();
	m_TextureID = g_Engine->GetModule<RendererDX11>()->GetTextureManager().LoadTexture("resources/textures/piggy.png");
}

void SimpleTexturedVC::Destroy()
{
	SimpleVisualComponent::Destroy();
	g_Engine->GetModule<RendererDX11>()->GetTextureManager().DeleteTexture(m_TextureID);
}
