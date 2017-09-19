#pragma once
#include "util/math/Mat.h"

class Camera
{
public:
    Camera(float fov, float AspectRatio);

    void Init();

    void Update(float dt);
	void Zoom(float distance);

    inline void SetPosition(const Vec2& pos) { m_Position = pos; }
    inline void SetPosition(const Vec3& pos) { m_Position = pos; }
    
    inline void SetMoveVelocity(const Vec3& vel) { m_MoveVelocity = vel; }

    inline const Vec3& GetMoveVelocity() const { return m_MoveVelocity; }
    inline Vec3& GetMoveVelocity() { return m_MoveVelocity; }

    inline Mat3x3& GetViewMatrix() { return m_ViewMatrix; }
    inline Mat3x3& GetProjectionMatrix() { return m_ProjectionMatrix; }

private:
    //Up is by default Y axis
    void BuildProjectionMatrix();
    void BuildViewMatrix();
    //Runtime Data
    Mat3x3 m_ViewMatrix;
    Mat3x3 m_ProjectionMatrix;

    Vec3 m_Position;
    Vec3 m_LookAtPoint;

    Vec3 m_MoveVelocity;

    //m_Position is the postion of the camera screen => m_Position + m_Offeset = Center Of Projection
    Vec3 m_CenterOfProjectionOffset;

    //Camera Settigns;
    float m_FOV;
    float m_AspectRatio;
    int m_ScreenWidth;
    int m_ScreenHeight;
	float m_Zoom = 0.0f;

};

