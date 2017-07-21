#include "Engine.h"
#include "../rendering/Renderer.h"
#include "World.h"
#include "../input/IInput.h"
#include "../physics/Physics.h"
#include "SystemSettings.h"

Engine::Engine()
{
}

void Engine::Init(const SystemSettings* settings)
{
	if (settings)
	{
		m_Settings.reset(new SystemSettings(*settings));
	}
	m_Window.reset(new Window());
	m_Window->Init(this);

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
		m_Window->Update();
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

void Engine::MakeWindow(const WindowInfo& info)
{

	m_Window.reset(new Window());
	m_Window->MakeWindow(&info);
}

Engine* Engine::GetEngine()
{
	if (!s_Engine)
	{
		std::lock_guard<std::mutex> lg(s_SingletonMutex);
		if (!s_Engine)
		{
			s_Engine = new Engine();
			return s_Engine;
		}
		return s_Engine;
	}
	return s_Engine;
}

Engine* Engine::s_Engine{ nullptr };
std::mutex Engine::s_SingletonMutex;

Engine::~Engine()
{
}
