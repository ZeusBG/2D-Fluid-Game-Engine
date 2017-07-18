#include "Engine.h"
#include "rendering/Renderer.h"
#include "World.h"
#include "IInput.h"
#include "Physics.h"
#include "SystemSettings.h"

Engine::Engine()
{
}

void Engine::Init()
{
	m_Settings.reset(new SystemSettings);
	m_Settings->SetScreenWidth(800);
	m_Settings->SetScreenHeight(600);

	m_Renderer.reset(new Renderer());
	m_Renderer->Init(this);
	m_World.reset(new World());
	m_World->Init(this);
}

void Engine::Run()
{
	m_IsRunning = true;
	m_TimeStarted = std::chrono::steady_clock::now();
	float delta = 0.0f;

	while (m_IsRunning)
	{
		TimePoint loopStart = std::chrono::steady_clock::now();
		m_Input->Update();
		m_World->Update(delta);
		m_Physics->Update(delta);
		m_Renderer->Render();

		TimePoint loopEnd = std::chrono::steady_clock::now();
		delta = std::chrono::duration_cast<std::chrono::microseconds>(loopEnd - loopStart).count() / 1000.0f;
		
	}

}

void Engine::Stop()
{
	m_IsRunning = false;
}

void Engine::LoadMap()
{
}

void Engine::PopState()
{
}

float Engine::TimeSinceStart()
{
	return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - m_TimeStarted).count() / 1000.0f;
}

void Engine::PushState(const GameState& state)
{
}

Engine::~Engine()
{
}
