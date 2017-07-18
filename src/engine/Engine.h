#pragma once
#include "GameState.h"
#include "StateStack.h"
class IRenderer;
class World;
class IInput;
class Engine
{
	IRenderer* m_Renderer;
	World* m_World;
	IInput* m_Input;

	StateStack m_StateStack;

	bool m_IsRunning;

public:
	void Init();
	void Run();
	void Stop();
	void LoadMap();
	void PushState(const GameState& state);
	void PopState();

	Engine();
	~Engine();
};

