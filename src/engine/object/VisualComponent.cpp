#include "engine/rendering/IShader.h"
#include "engine/rendering/shaderobjects/SimpleVS.h"
#include "engine/rendering/shaderobjects/SimplePS.h"
#include "engine/core/Engine.h"
#include "VisualComponent.h"
#include "engine/rendering/RenderCommander.h"
VisualComponent::VisualComponent()
{
}

void VisualComponent::Init()
{

	auto device = Engine::GetEngine()->GetModule<RendererDX11>()->GetDevice();
	m_Mesh.InitializeBuffers(device, this);
	m_VertexShader->Init();
	m_PixelShader->Init();
}

void VisualComponent::AddVertex(float x, float y)
{
}

void VisualComponent::Render()
{
	m_PixelShader->BindData(this);
	m_VertexShader->BindData(this);
	m_Mesh.RenderBuffers();
	auto renderCommander = Engine::GetEngine()->GetModule<RenderCommanderDx11>();
	renderCommander->DrawIndexed(m_Mesh.GetIndicesCount(), 0, 0);
}

void VisualComponent::Update(float delta)
{
}