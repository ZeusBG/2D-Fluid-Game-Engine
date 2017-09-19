#pragma once
#include "engine/rendering/IRenderer.h"
#include <rapidjson/fwd.h>
#include <string>
#include <memory>
#include <d3d11_1.h>
#include <d3dcompiler.h>

class IShader;
struct IShaderDeleter;

using SharedShaderPtr = std::shared_ptr<IShader>;
using UniqueShaderPtr = std::unique_ptr<IShader, IShaderDeleter>;

class VisualComponent;
class IShader
{
public:
    IShader(const char* fileName) : m_FileName(fileName) {}
	IShader() {}
    virtual void Init() = 0;
    virtual void Destroy() = 0;

    //TODO istoilov : figure out generic way to pass down params
    virtual void UpdateShaderParams() {};

	//TODO remvoe ID3D11DeviceContext from abstraction
    virtual void BindData(VisualComponent* vc) = 0;

	virtual void DeSerializeFromJSON(const rapidjson::Value& val);

    //TODO make facotry for shaders
    template<typename T>
    static SharedShaderPtr ShaderSharedPtr(const char* fileName);

protected:
    std::string m_FileName;
};

template <typename T>
SharedShaderPtr IShader::ShaderSharedPtr(const char* fileName)
{
    return std::make_shared<T>(fileName);
}
