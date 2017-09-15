#include "GameClient.h"
#include "SimpleEntity.h"
#include "ObjectsFactory.h"

GameClient::GameClient()
{
    m_Engine.reset(Engine::GetEngine());
}

void GameClient::Init(const SystemSettings& settings)
{
    m_Engine->SetSystemSettings(settings);
    m_Engine->Init(settings);
    m_Engine->LoadMap("resources/levels/EmptyLevel.json");
}

GameClient::~GameClient()
{
}
void GameClient::Start()
{
	m_NetManager->SetEngine(m_Engine.get());
	m_NetManager->Start();
}

void GameClient::InitServer()
{
	m_NetManager = std::make_shared<ServerController>();
}

void GameClient::InitClient()
{
	m_NetManager = std::make_shared<ClientController>();
}

void GameClient::StartSinglePlayer()
{
	m_Engine->LoadMap("resources/Levels/SimpleLevel.json");
	m_Engine->Run();
}

void GameClient::InitFromFile(const char* fileName)
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