#pragma once
#include "SimpleTexturedPS.h"
#include "engine/core/Engine.h"
#include "engine/rendering/RenderCommander.h"

#include <d3d11_1.h>
#include <d3dcompiler.h>


IMPLEMENT_METADATA(SimpleTexturedPS);

void SimpleTexturedPS::Init()
{
	SimplePS::Init();
	g_Engine->GetModule<RenderCommanderDx11>()->CreateSampler2D(&m_sampleState);
}

void SimpleTexturedPS::Destroy()
{
	SimplePS::Destroy();
}

void SimpleTexturedPS::BindData(VisualComponent* vc)
{
	SimplePS::BindData(vc);
	g_Engine->GetModule<RenderCommanderDx11>()->SetSampler2D(&m_sampleState);
}
