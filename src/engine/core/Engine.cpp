#include "Engine.h"
#include "../rendering/RendererDX11.h"
#include "World.h"
#include "../input/Input.h"
#include "../physics/Physics.h"
#include "SystemSettings.h"

Engine::Engine()
{
}

void Engine::Init(const SystemSettings settings)
{
	m_Settings = settings;
	m_EngineModules.push_back(new Window());
	m_EngineModules.back()->Init(this);

	m_EngineModules.push_back(new Input());
	m_EngineModules.back()->Init(this);

	m_EngineModules.push_back(new RendererDX11());
	m_EngineModules.back()->Init(this);

	m_EngineModules.push_back(new World());
	m_EngineModules.back()->Init(this);
}

void Engine::Run()
{
	m_IsRunning = true;
	m_EngineClock.Start();
	float delta = 0.0f;

	while (m_IsRunning)
	{
		for (IModule* module : m_EngineModules)
		{
			module->Update(delta);
		}
		delta = m_EngineClock.MeasureTime();
	}

	Destroy();
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
	return m_EngineClock.GetTimeSinceStart();
}

void Engine::PushState(const GameState& state)
{
}

void Engine::Destroy()
{
	for (IModule* module : m_EngineModules)
	{
		module->Destroy();
	}
}

void Engine::AddEntity(std::shared_ptr<Entity> entity)
{
	GetModule<World>()->AddEntity(entity);
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
