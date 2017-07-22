#pragma once
#include "engine/rendering/IRenderer.h"

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
    IShader(const char* fileName) :m_FileName(fileName) {}
    virtual void Init() = 0;
    virtual void Destroy() = 0;
    virtual void BindData(const VisualComponent* vc) = 0;

    //TODO make facotry for shaders
    template<typename T>
    static SharedShaderPtr ShaderSharedPtr(const char* fileName);

protected:
    std::string m_FileName;
};

struct IShaderDeleter {
    void operator()(IShader* p) const {
        p->Destroy();
        delete p;
    }
};

template <typename T>
SharedShaderPtr IShader::ShaderSharedPtr(const char* fileName)
{
    T* shader = new T(fileName);
    return SharedShaderPtr(shader, IShaderDeleter());
}
