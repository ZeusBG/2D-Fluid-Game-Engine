#include "engine/rendering/IShader.h"
#include "engine/rendering/shaderobjects/SimpleVS.h"
#include "engine/rendering/shaderobjects/SimplePS.h"
#include "engine/core/Engine.h"
#include "VisualComponent.h"

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

void VisualComponent::Render(ID3D11DeviceContext* context)
{
	m_PixelShader->BindData(context, this);
	m_VertexShader->BindData(context, this);
	m_Mesh.RenderBuffers(context);
	context->DrawIndexed(m_Mesh.GetIndicesCount(), 0, 0);
}

void VisualComponent::Update(float delta)
{
}