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
    std::shared_ptr<Entity> simpleEntity(std::static_pointer_cast<Entity>(ObjectsFactory::CreteObject("SimpleEntity")));
    m_Engine->AddEntity(simpleEntity);
}

GameClient::~GameClient()
{
}
