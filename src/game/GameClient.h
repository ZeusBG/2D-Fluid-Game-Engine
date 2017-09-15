#pragma once
#include <memory>
#include <fstream>
#include "engine/core/Engine.h"
#include "engine/core/SystemSettings.h"
#include "networking/server/ServerController.h"
#include "networking/client/ClientController.h"
#include "networking/NetworkManager.h"
class GameClient
{
	std::unique_ptr<Engine> m_Engine;
	std::shared_ptr<NetworkManager> m_NetManager;
	
	void Start();
public:
	GameClient();
	~GameClient();

	std::unique_ptr<Engine>& GetEngine() { return m_Engine; }
	void Init(const SystemSettings& settings);
	inline void SetNetworkInfo(const NetInfo& info) { m_NetManager->SetNetInfo(info); }
	void InitServer();
	void InitClient();
	void StartSinglePlayer();
	void InitFromFile(const char* fileName);

};

