#include "TexturedQuad.h"
#include "engine/core/Engine.h"
#include "engine/rendering/RenderCommander.h"

#include <rapidjson/document.h>

TexturedQuad::TexturedQuad()
{
	TexturedVertex v1;
	v1.Vertex = { 1.0f, 1.0f };
	v1.TextureCoord = { 0,0 };
	
	TexturedVertex v2;
	v2.Vertex = { -1.0f, 1.0f };
	v2.TextureCoord = { 1,0 };
	
	TexturedVertex v3;
	v3.Vertex = { -1.0f, -1.0f };
	v3.TextureCoord = { 1,1 };

	TexturedVertex v4;
	v4.Vertex = { 1.0f, -1.0f };
	v4.TextureCoord = { 0,1 };
	m_Vertices.push_back(v1);
	m_Vertices.push_back(v2);
	m_Vertices.push_back(v3);
	m_Vertices.push_back(v4);

	m_Indices = { 2, 1, 0, 0, 3, 2 };
}

void TexturedQuad::InitializeBuffers(VisualComponent* visualComponent)
{
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;

	ZeroMemory(&vertexBufferDesc, sizeof(D3D11_BUFFER_DESC));
	ZeroMemory(&indexBufferDesc, sizeof(D3D11_BUFFER_DESC));

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(TexturedVertex) * m_Vertices.size();
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	CreateBuffer(vertexBufferDesc, &m_VertexBuffer, m_Vertices.data());

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned int)* m_Indices.size();
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	CreateBuffer(indexBufferDesc, &m_IndexBuffer, m_Indices.data());
}

void TexturedQuad::BindData() const
{
	unsigned int stride;
	unsigned int offset;

	// Set vertex buffer stride and offset.
	stride = sizeof(TexturedVertex);
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	auto renderCommander = g_Engine->GetModule<RenderCommanderDx11>();
	renderCommander->SetVertexBuffers(&m_VertexBuffer, stride, offset);
	// Set the index buffer to active in the input assembler so it can be rendered.
	renderCommander->SetIndexBuffers(m_IndexBuffer, DataSizeFormat::R32_UINT, 0);
	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	renderCommander->SetTopology(Topology::TRIANGLE_LIST);
	return;
}

void TexturedQuad::Destroy()
{
	auto renderCommander = Engine::GetEngine()->GetModule<RenderCommanderDx11>();
	renderCommander->ReleaseResource(m_IndexBuffer, ResourceType::Buffer);
	renderCommander->ReleaseResource(m_VertexBuffer, ResourceType::Buffer);
}

void TexturedQuad::DeSerializeFromJSON(const rapidjson::Value& val)
{
}
