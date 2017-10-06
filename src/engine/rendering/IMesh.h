#pragma once

// Forward declarations for rapidjson
#include <rapidjson/fwd.h>

class VisualComponent;
struct D3D11_BUFFER_DESC;
struct ID3D11Buffer;

class IMesh
{
protected:
	void CreateBuffer(const D3D11_BUFFER_DESC& desc, ID3D11Buffer** buffer, void* initialData = nullptr);
	void ReleaseBuffer(ID3D11Buffer** buffer);
public:
	virtual void InitializeBuffers(VisualComponent* visualComponent) = 0;
	virtual void BindData() const = 0;
	virtual void Destroy() = 0;
	virtual void DeSerializeFromJSON(const rapidjson::Value& val) = 0;
	virtual unsigned GetVerticesCount() const = 0;
	virtual unsigned GetIndicesCount() const = 0;
protected:
};