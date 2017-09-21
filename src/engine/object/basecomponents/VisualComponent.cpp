#include "engine/rendering/IShader.h"
#include "engine/rendering/shaderobjects/SimpleVS.h"
#include "engine/rendering/shaderobjects/SimplePS.h"
#include "engine/core/Engine.h"
#include "engine/object/basecomponents/VisualComponent.h"
#include "engine/rendering/RenderCommander.h"

#include <rapidjson/document.h>

IMPLEMENT_METADATA(VisualComponent)

VisualComponent::VisualComponent()
{
}

void VisualComponent::Init()
{
    m_Mesh.InitializeBuffers(this);
    m_VertexShader->Init();
    m_PixelShader->Init();
}

void VisualComponent::Destroy()
{
    m_PixelShader->Destroy();
    m_VertexShader->Destroy();
    m_Mesh.Destroy();
}

void VisualComponent::DeSerializeFromJSON(const rapidjson::Value& val)
{
	if(val.HasMember("VertexShader"))
		m_VertexShader->DeSerializeFromJSON(val["VertexShader"]);
	if (val.HasMember("PixelShader"))
		m_PixelShader->DeSerializeFromJSON(val["PixelShader"]);
	if (val.HasMember("Mesh"))
		m_Mesh.DeSerializeFromJSON(val["Mesh"]);
}

void VisualComponent::AddVertex(float x, float y)
{
	m_Mesh.AddVertex(x, y);
}

void VisualComponent::Update(float delta)
{
    m_PixelShader->BindData(this);
    m_VertexShader->BindData(this);
    m_Mesh.RenderBuffers();
    auto renderCommander = Engine::GetEngine()->GetModule<RenderCommanderDx11>();
    renderCommander->DrawIndexed(m_Mesh.GetIndicesCount(), 0, 0);
}