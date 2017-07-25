#include "GameClient.h"
#include "SimpleEntity.h"


GameClient::GameClient()
{
	m_Engine.reset(Engine::GetEngine());
}

void GameClient::Init(const SystemSettings& settings)
{
	m_Engine->SetSystemSettings(settings);
	m_Engine->Init(settings);
	std::shared_ptr<Entity> simpleEntity(new SimpleEntity());
	m_Engine->AddEntity(simpleEntity);
}

GameClient::~GameClient()
{
}
