#pragma once
#include "engine/core/IModule.h"
#include "engine/camera/Camera.h"

#include "util/Collections.h"


typedef std::shared_ptr<Camera> CameraSharedPtr;

class Engine;
class CameraHandler : public IModule
{
public:
    virtual void Init(Engine* engine);

    virtual void Start();
    virtual void Update(float dt);

    virtual void Destroy();
    virtual const char* GetName() { return "Camera Handler"; }

    inline Camera* GetActiveCamera() { return m_ActiveCamera; }

private:
    AVector<Camera> m_CameraNodes;
    Camera* m_ActiveCamera;
};

#define g_CameraHandler Engine::GetEngine()->GetModule<CameraHandler>()

