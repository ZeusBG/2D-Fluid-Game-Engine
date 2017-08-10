#include <SDL.h>
#include <thread>

#include "engine/rendering/RendererDX11.h"

#include "engine/core/World.h"
#include "engine/core/SystemSettings.h"
#include "engine/rendering/RenderCommander.h"
#include "engine/core/Engine.h"

#include "engine/input/InputHandler.h"

#include "engine/physics/Physics.h"
#include "engine/logging/Logging.h"
Engine::Engine()
{
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

    while (m_IsRunning)
    {
        m_EngineClock.MeasureTime();
        for (const auto& module : m_EngineModules)
        {
            module->Update(delta);
        }
        GetModule<IRenderer>()->DoRenderingCommands();
        delta = m_EngineClock.MeasureTime();

        Sync(delta);
    }
}

void Engine::Stop()
{
    m_IsRunning = false;
}

void Engine::LoadMap()
{
}

void Engine::PopState()
{
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

void Engine::AddEntity(std::shared_ptr<Entity> entity)
{
    GetModule<World>()->AddEntity(entity);
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
