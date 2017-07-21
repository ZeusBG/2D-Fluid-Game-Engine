#include "GameClient.h"



GameClient::GameClient()
{
	m_Engine.reset(Engine::GetEngine());
}

void GameClient::Init(const SystemSettings& settings)
{
	m_Engine->SetSystemSettings(settings);
	m_Engine->Init(&settings);
}

GameClient::~GameClient()
{
}
