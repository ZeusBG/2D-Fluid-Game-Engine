#pragma once
#include "SimpleVisualComponent.h"
#include "engine/core/Engine.h"
#include "engine/rendering/SimplePS.h"
#include "engine/rendering/SimpleVS.h"

SimpleVisualComponent::SimpleVisualComponent()
{
	m_PixelShader = std::static_pointer_cast<IShader>(IShader::ShaderSharedPtr<SimplePS>("src/engine/rendering/shaders/SimpleShader.fx"));
	m_VertexShader = std::static_pointer_cast<IShader>(IShader::ShaderSharedPtr<SimpleVS>("src/engine/rendering/shaders/SimpleShader.fx"));

	AVector<float> vertices;
	vertices.push_back(0.0f);  vertices.push_back(0.1f);
	vertices.push_back(0.25f); vertices.push_back(0.75f);
	vertices.push_back(0.75f); vertices.push_back(0.25f);
	vertices.push_back(0.5f); vertices.push_back(0.5f);
	//vertices.push_back(0.3f); vertices.push_back(0.3f);
	//vertices.push_back(0.6f); vertices.push_back(0.4f);
	m_Mesh.SetVertices(vertices);
}
