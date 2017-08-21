#include "engine/camera/Camera.h"
#include "engine/core/Engine.h"

Camera::Camera(float fov, float aspectRatio) :
    m_FOV(fov),
    m_AspectRatio(aspectRatio),
    m_CenterOfProjectionOffset(0.f, 0.f, .3f)
{
}


void Camera::Update(float dt)
{
    m_Position += m_MoveVelocity;

    BuildViewMatrix();
}

void Camera::BuildProjectionMatrix()
{
    m_ProjectionMatrix.SetRowI(Vec3(1.f / m_ScreenWidth, 0.f, 0.f));
    m_ProjectionMatrix.SetRowJ(Vec3(0.f, 1.f / m_ScreenHeight, 0.f));
    m_ProjectionMatrix.SetRowK(Vec3(0.f, 0.f, 0.f));
}

void Camera::BuildViewMatrix()
{
    //istoilov: Fixed axies for know as we do not plan to rotate the camera ... for now
    Vec3 xAxis = Vec3::BaseI;
    Vec3 yAxis = Vec3::BaseJ;
    Vec3 zAxis = Vec3::BaseK;

    m_ViewMatrix.SetRowI(xAxis);
    m_ViewMatrix.SetRowJ(yAxis);
    m_ViewMatrix.SetRowK(zAxis);

    m_ViewMatrix.Translate(-m_Position.x, -m_Position.y, 0.f);

}

void Camera::Init()
{
    const SystemSettings* settings = g_Engine->GetSettings();
    m_ScreenHeight = settings->ScreenHeight;
    m_ScreenWidth = settings->ScreenWidth;

    BuildViewMatrix();
    BuildProjectionMatrix();
}