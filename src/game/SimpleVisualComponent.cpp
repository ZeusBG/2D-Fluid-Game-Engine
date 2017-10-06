#pragma once
#include "SimpleVisualComponent.h"
#include "engine/core/Engine.h"
#include "engine/rendering/shaderobjects/SimplePS.h"
#include "engine/rendering/shaderobjects/SimpleVS.h"
#include "engine/rendering/mesh/SimpleQuad.h"

//remove

#include "game/SimpleTexturedVS.h"
#include "game/SimpleTexturedPS.h"
#include <rapidjson/document.h>
IMPLEMENT_METADATA(SimpleVisualComponent)

SimpleVisualComponent::SimpleVisualComponent()
{
    m_PixelShader = std::static_pointer_cast<IShader>(IShader::ShaderSharedPtr<SimpleTexturedPS>("src/engine/rendering/shaders/SimpleShader.fx"));
    m_VertexShader = std::static_pointer_cast<IShader>(IShader::ShaderSharedPtr<SimpleTexturedVS>("src/engine/rendering/shaders/SimpleShader.fx"));
	m_Mesh = std::make_shared<SimpleQuad>();
	
}

void SimpleVisualComponent::DeSerializeFromJSON(const rapidjson::Value& val)
{
	VisualComponent::DeSerializeFromJSON(val);
}