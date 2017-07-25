#include "engine/rendering/IShader.h"
#include "engine/rendering/SimpleVS.h"
#include "engine/rendering/SimplePS.h"
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

void VisualComponent::Update(float delta)
{
}