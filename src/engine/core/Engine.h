#pragma once
#include "engine/GameState.h"
#include "engine/StateStack.h"
#include "util/Collections.h"
#define NOMINMAX // Used for Windows.h
#include "Window.h"
#include "SystemSettings.h"
#include "engine/object/Entity.h"
#include "engine/time/Clock.h"
#include "networking/NetworkManager.h"
#include <mutex>
#include <chrono>


#define g_Engine Engine::GetEngine()

class Physics;
class IRenderer;
class World;
class IInput;
struct SystemSettings;
class RenderCommanderDx11;
struct ByteStream;

class Engine
{
    static Engine* s_Engine;
    static std::mutex s_SingletonMutex;

    Clock m_EngineClock;
    AVector<std::shared_ptr<IModule>> m_EngineModules;
	AVector<std::shared_ptr<Entity>> m_EntitiesToBeRemoved;

    const float m_FrameCap = 1.0f / 60.0f;
    StateStack m_StateStack;
    SystemSettings m_Settings;
    bool m_IsRunning;

	NetworkManager* m_NetworkManager;

    void Sync(float dt);
    Engine();
    void StartModules();
    void Destroy();
	void _RemoveEntity(EntitySP);
	void RemovePendingEntities();
public:
    void Init(const SystemSettings settings);
    void Run();
    void Stop();
    void LoadMap(const char* map);
    void PushState(const GameState& state);
    void PopState();
	void DoSnapShot(ByteStream* bs);
	void DoCreationSnapShot(ByteStream* bs);

    float TimeSinceStart();
    const SystemSettings* GetSettings() const { return &m_Settings; }
    void SetSystemSettings(const SystemSettings& settings) { m_Settings = settings; }
	inline void SetNetworkManager(NetworkManager* networkManager) { m_NetworkManager = networkManager; }
    void AddEntity(std::shared_ptr<Entity> entity);
	EntitySP GetEntityByID(int id);
	EntitySP CreateEntityWithID(const char* entity, int id);
	EntitySP CreateEntity(const  char* name);
	EntitySP CreateEntityFromType(int type);
	bool RemoveEntityByID(int id);

    template <typename T>
    std::shared_ptr<T> GetModule()
    {
        for (const auto& module : m_EngineModules)
        {
            std::shared_ptr<T> result = std::dynamic_pointer_cast<T>(module);
            if (result.get())
            {
                return result;
            }
        }
        return nullptr;
    }

    static Engine* GetEngine();
    ~Engine();
};

