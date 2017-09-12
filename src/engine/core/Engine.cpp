#include <SDL.h>
#include <thread>
#include <fstream>
#include "engine/core/World.h"
#include "engine/core/SystemSettings.h"
#include "engine/core/Engine.h"

#include "engine/rendering/RenderCommander.h"
#include "engine/rendering/RendererDX11.h"

#include "engine/input/InputHandler.h"
#include "engine/camera/CameraHandler.h"
#include "engine/physics/Physics.h"
#include "engine/logging/Logging.h"
#include "networking/networkutil/Buffer.h"
#include "game/ObjectsFactory.h"

// TODO remove this later
#include "game/SimpleVisualComponent.h"

#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
Engine::Engine()
{
	m_NetworkManager = nullptr;
}

void Engine::Init(const SystemSettings settings)
{
    m_Settings = settings;
    m_EngineModules.push_back(std::make_shared<Window>());
    m_EngineModules.back()->Init(this);

    m_EngineModules.push_back(std::make_shared<InputHandler>());
    m_EngineModules.back()->Init(this);

    m_EngineModules.push_back(std::make_shared<World>());
    m_EngineModules.back()->Init(this);

    m_EngineModules.push_back(std::make_shared<RendererDX11>());
    m_EngineModules.back()->Init(this);

    m_EngineModules.push_back(std::make_shared<RenderCommanderDx11>());
    m_EngineModules.back()->Init(this);

    m_EngineModules.push_back(std::make_shared<CameraHandler>());
    m_EngineModules.back()->Init(this);

	ObjectsFactory::LoadPrototypeFile("resources/EntityTypeMap.json");

}

void Engine::Sync(float delta)
{
    float timeLeft = (m_FrameCap - delta) * 1000;
    if (timeLeft < 0)
        return;
    LOG_L2(INFO, INFO, "Sleeping for %f", timeLeft);
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(timeLeft)));
}

void Engine::StartModules()
{
    for (const auto& m : m_EngineModules)
    {
        m->Start();
    }
}

void Engine::Run()
{
    m_IsRunning = true;
    StartModules();

    m_EngineClock.Start();
    float delta = 0.0f;
	float frameTime = 0.0f;
    while (m_IsRunning)
    {
		RemovePendingEntities();
        m_EngineClock.MeasureTime();
        for (const auto& module : m_EngineModules)
        {
            module->Update(delta);
        }
		if (m_NetworkManager != nullptr)
		{
			m_NetworkManager->HandleRecievedPackets();
			m_NetworkManager->DoSnapShot();
			m_NetworkManager->SendPendingPackets();
		}
        GetModule<IRenderer>()->DoRenderingCommands();
        frameTime = m_EngineClock.MeasureTime();
        Sync(frameTime);
		delta = frameTime + m_EngineClock.MeasureTime();
    }
}

void Engine::Stop()
{
    m_IsRunning = false;
}

void Engine::LoadMap(const char* map)
{
    // TODO: Make file reading on a separate thread
    std::ifstream ifs(map);
    bool t = ifs.good();
    rapidjson::IStreamWrapper isw(ifs);

    rapidjson::Document doc;
    doc.ParseStream(isw);

    GetModule<World>()->LoadLevel(doc);

}

void Engine::PopState()
{
}

void Engine::DoSnapShot(ByteStream* bsstream)
{
	GetModule<World>()->DoSnapShot(bsstream);
}

void Engine::DoCreationSnapShot(ByteStream * bs)
{
	GetModule<World>()->DoCreationSnapShot(bs);
}

float Engine::TimeSinceStart()
{
    return m_EngineClock.GetTimeSinceStart();
}

void Engine::PushState(const GameState& state)
{
}

void Engine::Destroy()
{
    for (const auto& module : m_EngineModules)
    {
        module->Destroy();
    }
}

void Engine::_RemoveEntity(EntitySP entity)
{
	GetModule<World>()->RemoveEntityByID(entity->GetID());
}

void Engine::RemovePendingEntities()
{
	for (const auto& entity : m_EntitiesToBeRemoved)
	{
		_RemoveEntity(entity);
	}
	m_EntitiesToBeRemoved.clear();
}

void Engine::AddEntity(std::shared_ptr<Entity> entity)
{
    GetModule<World>()->AddEntity(entity);
}

EntitySP Engine::GetEntityByID(int id)
{
	return GetModule<World>()->GetEntityByID(id);
}

EntitySP Engine::CreateEntityWithID(const char* name, int id)
{
	EntitySP entity = ObjectsFactory::CreteEntity(name);
	entity->SetID(id);
	return entity;
}

EntitySP Engine::CreateEntity(const char* name)
{
	auto entity = ObjectsFactory::CreteEntity(name);
	entity->AddComponent(std::make_shared<SimpleVisualComponent>());
	return entity;
}

EntitySP Engine::CreateEntityFromType(int type)
{
	auto entity = ObjectsFactory::CreateEntityFromType(type);
	return entity;
}

bool Engine::RemoveEntityByID(int id)
{
	auto entity = GetModule<World>()->GetEntityByID(id);
	if (!entity)
		return false;
	m_EntitiesToBeRemoved.push_back(GetModule<World>()->GetEntityByID(id));
	return true;
}

Engine* Engine::GetEngine()
{
    if (!s_Engine)
    {
        std::lock_guard<std::mutex> lg(s_SingletonMutex);
        if (!s_Engine)
        {
            s_Engine = new Engine();
            return s_Engine;
        }
        return s_Engine;
    }
    return s_Engine;
}

Engine* Engine::s_Engine{ nullptr };
std::mutex Engine::s_SingletonMutex;

Engine::~Engine()
{
    Destroy();
}
