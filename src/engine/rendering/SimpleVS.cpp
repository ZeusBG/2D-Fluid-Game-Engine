#pragma once

#include "engine/core/Engine.h"
#include "engine/rendering/SimpleVS.h"
#include "engine/rendering/IRenderer.h"

#include <d3d11_1.h>
#include <d3dcompiler.h>

void SimpleVS::Init()
{
	m_VSShader = Engine::GetEngine()->GetModule<IRenderer>()->CreateVSFromFile(m_FileName.data(), ShaderVersion::V4_0);
}

void SimpleVS::Destroy()
{
	Engine::GetEngine()->GetModule<IRenderer>()->DestroyPS(m_VSShader);
}

void SimpleVS::BindData(const VisualComponent* vc)
{

}
