#include "engine/rendering/IShader.h"
#include "engine/rendering/shaderobjects/SimpleVS.h"
#include "engine/rendering/shaderobjects/SimplePS.h"
#include "engine/core/Engine.h"
#include "engine/object/basecomponents/visualcomponent.h"
#include "engine/rendering/RenderCommander.h"

IMPLEMENT_METADATA(VisualComponent)

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

void VisualComponent::Destroy()
{
    m_PixelShader->Destroy();
    m_VertexShader->Destroy();
    m_Mesh.Destroy();
}

void VisualComponent::AddVertex(float x, float y)
{
}

void VisualComponent::Update(float delta)
{
    m_PixelShader->BindData(this);
    m_VertexShader->BindData(this);
    m_Mesh.RenderBuffers();
    auto renderCommander = Engine::GetEngine()->GetModule<RenderCommanderDx11>();
    renderCommander->DrawIndexed(m_Mesh.GetIndicesCount(), 0, 0);
}