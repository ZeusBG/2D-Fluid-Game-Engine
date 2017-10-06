#pragma once

#include <directxmath.h>
#include "engine/rendering/RendererDX11.h"
#include "util/Collections.h"
#include "engine/rendering/IMesh.h"

struct SimpleVertex
{
	DirectX::XMFLOAT2 Vertex;
};

class VisualComponent;
class SimpleQuad : public IMesh
{
public:
	SimpleQuad();

    virtual void InitializeBuffers(VisualComponent* visualComponent) override;
    virtual void BindData() const override;
	virtual void Destroy() override;
	virtual void DeSerializeFromJSON(const rapidjson::Value& val) override;
    unsigned GetVerticesCount() const override { return m_Vertices.size(); }
	unsigned GetIndicesCount() const override { return m_Indices.size(); }

private:
	ID3D11Buffer* m_VertexBuffer;
	ID3D11Buffer* m_IndexBuffer;

	AVector<SimpleVertex> m_Vertices;
	AVector<unsigned int> m_Indices;
};