#pragma once
#include "util/math/Mat.h"
#include "engine/object/Entity.h"

class Camera
{
public:
    Camera(float fov, float AspectRatio);

    void Init();

    void Update(float dt);

    inline Mat3x3& GetViewMatrix() { return m_ViewMatrix; }
    inline Mat3x3& GetProjectionMatrix() { return m_ProjectionMatrix; }

    inline void SetFollowEntity(EntitySP entity) { m_FollowEntity = entity; }

private:
    //Up is by default Y axis
    void BuildProjectionMatrix();
    void BuildViewMatrix();
    //Runtime Data
    Mat3x3 m_ViewMatrix;
    Mat3x3 m_ProjectionMatrix;

    Vec3 m_Position;
    Vec3 m_LookAtPoint;

    EntitySP m_FollowEntity;

    //m_Position is the postion of the camera screen => m_Position + m_Offeset = Center Of Projection
    Vec3 m_CenterOfProjectionOffset;

    //Camera Settigns;
    float m_FOV;
    float m_AspectRatio;
    int m_ScreenWidth;
    int m_ScreenHeight;

};