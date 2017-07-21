#pragma once
#include "../GameState.h"
#include "../StateStack.h"
#include "../../util/Collections.h"
#include "Window.h"
#include "SystemSettings.h"
#include "../time/Clock.h"
#include <mutex>
#include <chrono>

class Physics;
class IRenderer;
class World;
class IInput;
struct SystemSettings;

class Engine
{
	static Engine* s_Engine;
	static std::mutex s_SingletonMutex;

	Clock m_EngineClock;
	AVector<IModule*> m_EngineModules;

	StateStack m_StateStack;
	SystemSettings m_Settings;
	bool m_IsRunning;
	Engine();

public:
	void Init(const SystemSettings settings);
	void Run();
	void Stop();
	void LoadMap();
	void PushState(const GameState& state);
	void PopState();

	float TimeSinceStart();
	const SystemSettings* GetSettings() const { return &m_Settings; }
	void SetSystemSettings(const SystemSettings& settings) { m_Settings = settings; }
	void Destroy();

	template <typename T>
	T* GetModule()
	{
		for (IModule* module : m_EngineModules)
		{
			T* result = dynamic_cast<T*>(module);
			if (result)
			{
				return result;
			}
		}
		return nullptr;
	}

	static Engine* GetEngine();
	~Engine();
};

