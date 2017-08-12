#include "engine/object/basecomponents/CameraComponent.h"

#include "engine/core/Engine.h"

#include "engine/camera/Camera.h"
#include "engine/camera/CameraHandler.h"

#include "util/math/MathUtils.h"

IMPLEMENT_METADATA(CameraComponent);

void CameraComponent::Init()
{
    m_Ratio = 0.f;
}


void CameraComponent::UpdateRatio(float dt)
{/*
    Camera* activeCamera = g_CameraHandler->GetActiveCamera();
    Vec3 targetVel = m_Owner->GetGlobalPosition3() - m_OwnerPrevPos;
    Vec3 currentVel = activeCamera->GetMoveVelocity();


    if (m_Ratio < 1.f && currentVel < targetVel) 
        m_Ratio += dt * 100.f;

    else if (m_Ratio >= 0.f && currentVel > targetVel)
        m_Ratio -= dt * 100.f;
    
    MathUtils::Clamp(m_Ratio, 0.f, 1.f);*/

}

void CameraComponent::Update(float dt)
{
    //UpdateRatio(dt);

    Camera* activeCamera = g_CameraHandler->GetActiveCamera();
    activeCamera->SetPosition(m_Owner->GetGlobalPosition());
    //*Vec3 currentVel = activeCamera->GetMoveVelocity();
    //Vec3 targetVel = m_Owner->GetGlobalPosition3() - m_OwnerPrevPos;

    //activeCamera->SetMoveVelocity(MathUtils::Lerp(currentVel, targetVel, m_Ratio));*/
   
    //m_OwnerPrevPos = m_Owner->GetGlobalPosition3();
}