#pragma once
#include "../GameState.h"
#include "../StateStack.h"
#include "../../util/Collections.h"
#include "Window.h"
#include "SystemSettings.h"
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
	typedef std::chrono::steady_clock::time_point TimePoint;

	TimePoint m_TimeStarted;

	std::unique_ptr<IRenderer> m_Renderer;
	std::unique_ptr<World> m_World;
	std::unique_ptr<IInput> m_Input;
	std::unique_ptr<Physics> m_Physics;
	std::unique_ptr<Window> m_Window;

	AVector<IModule*> m_EngineComponents; // order ?
	StateStack m_StateStack;
	std::unique_ptr<SystemSettings> m_Settings;
	bool m_IsRunning;
	Engine();


public:
	void Init(const SystemSettings* settings);
	void Run();
	void Stop();
	void LoadMap();
	void PushState(const GameState& state);
	void PopState();
	void MakeWindow(const WindowInfo& info);

	float TimeSinceStart();
	const SystemSettings* GetSettings() const { return m_Settings.get(); }
	void SetSystemSettings(const SystemSettings& settings) { m_Settings.reset(new SystemSettings(settings)); }
	const Window* GetWindow() const { return m_Window.get(); }

	static Engine* GetEngine();
	~Engine();
};

