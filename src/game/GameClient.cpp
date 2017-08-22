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
    m_Engine->LoadMap("resources/levels/SimpleLevel.json");
}

GameClient::~GameClient()
{
}
