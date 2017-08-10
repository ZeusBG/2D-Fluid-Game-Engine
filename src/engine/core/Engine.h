#pragma once
#include "../GameState.h"
#include "../StateStack.h"
#include "../../util/Collections.h"
#include "Window.h"
#include "SystemSettings.h"
#include "engine/object/Entity.h"
#include "../time/Clock.h"
#include <mutex>
#include <chrono>


#define g_Engine Engine::GetEngine()

class Physics;
class IRenderer;
class World;
class IInput;
struct SystemSettings;
class RenderCommanderDx11;
class Engine
{
	static Engine* s_Engine;
	static std::mutex s_SingletonMutex;

	Clock m_EngineClock;
	AVector<std::shared_ptr<IModule>> m_EngineModules;

	const float m_FrameCap = 1.0f / 60.0f;
	StateStack m_StateStack;
	SystemSettings m_Settings;
	bool m_IsRunning;

	void Sync(float dt);
	Engine();
    void StartModules();
    void Destroy();
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

	void AddEntity(std::shared_ptr<Entity> entity);

	template <typename T>
    std::shared_ptr<T> GetModule()
	{
		for (const auto& module : m_EngineModules)
		{
            std::shared_ptr<T> result = std::dynamic_pointer_cast<T>(module);
			if (result.get())
			{
				return result;
			}
		}
		return nullptr;
	}

	static Engine* GetEngine();
	~Engine();
};

