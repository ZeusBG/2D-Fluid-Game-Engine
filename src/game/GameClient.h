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
	
	void Start()
	{
		m_NetManager->SetEngine(m_Engine.get());
		m_NetManager->Start();
	}

	void InitNetManager()
	{

	}
public:
	GameClient();
	~GameClient();

	std::unique_ptr<Engine>& GetEngine() { return m_Engine; }
	void Init(const SystemSettings& settings);
	inline void SetNetworkInfo(const NetInfo& info) { m_NetManager->SetNetInfo(info); }
	void InitServer()
	{
		m_NetManager = std::make_shared<ServerController>();
		//Start();
	}

	void InitClient()
	{
		m_NetManager = std::make_shared<ClientController>();
		//Start();
	}

	void StartSinglePlayer()
	{
		m_Engine->Run();
	}

	void InitFromFile(const char* fileName)
	{
		std::ifstream is;
		is.open(fileName);
		if (is.bad())
			return;

		std::string startType;
		std::getline(is, startType);

		if (startType == "SinglePlayer")
		{
			StartSinglePlayer();
			return;
		}

		if (startType == "Client")
		{
			InitClient();
		}
		else if (startType == "Server")
		{
			InitServer();
		}

		std::string ip, port;
		std::getline(is, ip);
		std::getline(is, port);
		SetNetworkInfo({ ip, static_cast<unsigned int>(std::stoi(port)) });
		m_NetManager->Init(ip.c_str(), static_cast<unsigned int>(std::stoi(port)));
		Start();


	}
};

