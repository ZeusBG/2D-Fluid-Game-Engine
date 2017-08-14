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
    m_Engine->LoadMap("Levels/SimpleLevel.json");

    simpleEntity->AddComponent(ObjectsFactory::CreateComponent("SimpleVisualComponent"));
    simpleEntity->AddComponent(ObjectsFactory::CreateComponent("CharacterControllerComponent"));
    simpleEntity->AddComponent(ObjectsFactory::CreateComponent("CameraComponent"));


    std::shared_ptr<Entity> simpleEntity2(new SimpleEntity());
    simpleEntity2->AddComponent(ObjectsFactory::CreateComponent("SimpleVisualComponent"));
    m_Engine->AddEntity(simpleEntity2);

    
}

GameClient::~GameClient()
{
}
