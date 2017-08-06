#include "GameClient.h"
#include "SimpleEntity.h"
#include "ObjectsFactory.h"
#include "game/SimpleVisualComponent.h"
#include "game/CharacterControllerComponent.h"

#include "engine/rendering/shaderobjects/SimplePS.h"
#include "engine/rendering/shaderobjects/SimpleVS.h"

#include "engine/camera/CameraHandler.h"

GameClient::GameClient()
{
    m_Engine.reset(Engine::GetEngine());
}

void GameClient::Init(const SystemSettings& settings)
{
    m_Engine->SetSystemSettings(settings);
    m_Engine->Init(settings);
    std::shared_ptr<Entity> simpleEntity(std::static_pointer_cast<Entity>(ObjectsFactory::CreteObject("SimpleEntity")));

    simpleEntity->AddComponent(new SimpleVisualComponent());
    simpleEntity->AddComponent(new CharacterControllerComponent());

    m_Engine->AddEntity(simpleEntity);

    std::shared_ptr<Entity> simpleEntity2(new SimpleEntity());
    simpleEntity2->AddComponent(new SimpleVisualComponent());
    //simpleEntity2->AddTranslate(Vec2(0.5f, 0.5f));
    m_Engine->AddEntity(simpleEntity2);

    Camera* camera = g_CameraHandler->GetActiveCamera();
    camera->SetFollowEntity(simpleEntity);

    int a = 0;
}

GameClient::~GameClient()
{
}
