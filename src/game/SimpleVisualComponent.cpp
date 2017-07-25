#pragma once
#include "SimpleVisualComponent.h"
#include "engine/core/Engine.h"
#include "engine/rendering/SimplePS.h"
#include "engine/rendering/SimpleVS.h"

SimpleVisualComponent::SimpleVisualComponent()
{
	m_PixelShader = std::static_pointer_cast<IShader>(IShader::ShaderSharedPtr<SimplePS>("src/engine/rendering/shaders/SimpleShader.fx"));
	m_VertexShader = std::static_pointer_cast<IShader>(IShader::ShaderSharedPtr<SimpleVS>("src/engine/rendering/shaders/SimpleShader.fx"));

	AVector<XMFLOAT2> vertices;
	vertices.push_back({ -1.0f, -1.0f });
	vertices.push_back({ 0.0f, 1.0f });
	vertices.push_back({ 1.0f, 0.0f });
	vertices.push_back({ -1.0f, 1.0f });

	m_Mesh.SetVertices(vertices);

	m_Mesh.AddIndex(0, 1, 2);
	m_Mesh.AddIndex(0, 3, 2);
}
