#pragma once
#include "SimpleVisualComponent.h"
#include "engine/core/Engine.h"
#include "engine/rendering/shaderobjects/SimplePS.h"
#include "engine/rendering/shaderobjects/WorldTransformVSObject.h"

SimpleVisualComponent::SimpleVisualComponent()
{
    m_PixelShader = std::static_pointer_cast<IShader>(IShader::ShaderSharedPtr<SimplePS>("src/engine/rendering/shaders/SingleColorPS.hlsl"));
    m_VertexShader = std::static_pointer_cast<IShader>(IShader::ShaderSharedPtr<WorldTransformVSObject>("src/engine/rendering/shaders/WorldTransformVS.hlsl"));

    AVector<XMFLOAT2> vertices;
    vertices.push_back({  0.2f,  0.2f  }); //0
    vertices.push_back({ -0.2f,  0.2f  }); //1
    vertices.push_back({ -0.2f, -0.2f });  //2
    vertices.push_back({  0.2f, -0.2f });  //3

    m_Mesh.SetVertices(vertices);

    m_Mesh.AddIndex(2, 1, 0);
    m_Mesh.AddIndex(0, 3, 2);

   /* AVector<XMFLOAT2> vertices;
    vertices.push_back({ -1.0f, -1.0f });
    vertices.push_back({ 0.0f, 1.0f });
    vertices.push_back({ 1.0f, 0.0f });
    vertices.push_back({ 1.0f, -1.0f });

    m_Mesh.SetVertices(vertices);

    m_Mesh.AddIndex(0, 1, 2);
    m_Mesh.AddIndex(0, 2, 3);*/
}
