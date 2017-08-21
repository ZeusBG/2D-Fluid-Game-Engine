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

    simpleEntity->AddComponent(ObjectsFactory::CreateComponent("SimpleVisualComponent"));
    simpleEntity->AddComponent(ObjectsFactory::CreateComponent("CharacterControllerComponent"));
    simpleEntity->AddComponent(ObjectsFactory::CreateComponent("CameraComponent"));

    m_Engine->AddEntity(simpleEntity);

    std::shared_ptr<Entity> simpleEntity2(new SimpleEntity());
    simpleEntity2->AddComponent(ObjectsFactory::CreateComponent("SimpleVisualComponent"));
    m_Engine->AddEntity(simpleEntity2);

    
}

GameClient::~GameClient()
{
}
