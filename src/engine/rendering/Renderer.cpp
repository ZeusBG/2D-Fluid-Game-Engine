#pragma once
#include "Renderer.h"
#include "../SystemSettings.h"
#include "../Engine.h"

Renderer::Renderer() {}
Renderer::~Renderer() {}

void Renderer::Init(Engine* engine)
{
	const SystemSettings* settings = engine->GetSettings();
	m_ScreenWidth = settings->GetScreenWidth();
	m_ScreenHeight = settings->GetScreenHeight();
}

void Renderer::Render()
{

}

const char* Renderer::GetName() { return "Renderer"; }