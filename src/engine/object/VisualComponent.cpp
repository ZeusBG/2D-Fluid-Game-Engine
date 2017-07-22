#include "engine/rendering/IShader.h"
#include "engine/rendering/SimpleVS.h"
#include "engine/rendering/SimplePS.h"

#include "VisualComponent.h"

void VisualComponent::Init()
{
    //m_VertexShader = IShader::ShaderSharedPtr<SimpleVS>("WorldTransformVS.hlsl");
    //m_PixelShader = IShader::ShaderSharedPtr<SimpleVS>("SingleColorPS.hlsl");
}

void VisualComponent::AddVertex(float x, float y)
{
}

void VisualComponent::Update(float delta)
{

}