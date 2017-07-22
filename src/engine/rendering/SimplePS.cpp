#pragma once
#include "IRenderer.h"
#include "../core/Engine.h"
#include "SimplePS.h"

#include <d3d11_1.h>
#include <d3dcompiler.h>

void SimplePS::Init()
{
	m_PSShader = Engine::GetEngine()->GetModule<IRenderer>()->CreatePSFromFile(m_FileName.data(), ShaderVersion::V4_0);
}

void SimplePS::Destroy()
{
	Engine::GetEngine()->GetModule<IRenderer>()->DestroyPS(m_PSShader);
}

void SimplePS::BindData(const VisualComponent* vc)
{
}
