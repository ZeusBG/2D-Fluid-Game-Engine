#pragma once
#include <memory>
#include "../engine/Engine.h"
class GameClient
{
	std::unique_ptr<Engine> m_Engine;
public:
	GameClient();
	~GameClient();

	void Start() { m_Engine->Run(); }
};

