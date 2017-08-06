#include "engine/camera/CameraHandler.h"

void CameraHandler::Init(Engine* engine)
{
    // TODO istoilov : Fix hardcoded cameras

    m_CameraNodes.push_back(Camera(45.f, 4.f / 3.f));
    m_CameraNodes.back().Init();
    m_ActiveCamera = &(m_CameraNodes[0]);
}

void CameraHandler::Start() {}

void CameraHandler::Update(float dt) 
{
    m_ActiveCamera->Update(dt);
}

void CameraHandler::Destroy() {}