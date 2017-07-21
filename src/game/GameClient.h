#pragma once
#include <memory>
#include "../engine/core/Engine.h"
#include "../engine/core/SystemSettings.h"

class GameClient
{
	std::unique_ptr<Engine> m_Engine;
public:
	GameClient();
	~GameClient();

	void Init(const SystemSettings& settings);
	void Start() { m_Engine->Run(); }
};

