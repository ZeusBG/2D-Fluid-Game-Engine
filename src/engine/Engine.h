#pragma once
#include "GameState.h"
#include "StateStack.h"
#include "../util/Collections.h"

#include <chrono>

class SystemSettings;
class Physics;
class IRenderer;
class World;
class IInput;
class Engine
{
	typedef std::chrono::steady_clock::time_point TimePoint;

	TimePoint m_TimeStarted;

	std::unique_ptr<IRenderer> m_Renderer;
	std::unique_ptr<World> m_World;
	std::unique_ptr<IInput> m_Input;
	std::unique_ptr<Physics> m_Physics;
	std::unique_ptr<SystemSettings> m_Settings;

	//AVector<Interface> m_EngineComponents; // order ?
	StateStack m_StateStack;
	bool m_IsRunning;

public:
	void Init();
	void Run();
	void Stop();
	void LoadMap();
	void PushState(const GameState& state);
	void PopState();

	float TimeSinceStart();
	const SystemSettings* GetSettings() const { return m_Settings.get(); }

	Engine();
	~Engine();
};

