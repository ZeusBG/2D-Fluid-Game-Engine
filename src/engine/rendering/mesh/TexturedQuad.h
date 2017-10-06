#pragma once

#include <directxmath.h>
#include "engine/rendering/RendererDX11.h"
#include "util/Collections.h"
#include "IMesh.h"

struct TexturedVertex
{
	DirectX::XMFLOAT2 Vertex;
	DirectX::XMFLOAT2 TextureCoord;
};

class VisualComponent;
class TexturedQuad : public IMesh
{
public:
	TexturedQuad();

    virtual void InitializeBuffers(VisualComponent* visualComponent) override;
    virtual void BindData() const override;
	virtual void Destroy() override;
	virtual void DeSerializeFromJSON(const rapidjson::Value& val) override;
    unsigned GetVerticesCount() const override { return m_Vertices.size(); }
	unsigned GetIndicesCount() const override { return m_Indices.size(); }

private:
	ID3D11Buffer* m_VertexBuffer;
	ID3D11Buffer* m_IndexBuffer;

	AVector<TexturedVertex> m_Vertices;
	AVector<unsigned int> m_Indices;
};