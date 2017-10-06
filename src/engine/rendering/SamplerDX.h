#pragma once

struct SamplerDesc
{

};

class SamplerDX
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
	virtual void InitConstantBuffers() {}

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
