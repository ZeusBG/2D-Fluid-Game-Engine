#pragma once
#include "engine/object/basecomponents/Component.h"
#include "util/math/Vec.h"

/*
istoilov:

- Introduce internal handling of multiple Camera object definition
    - some sort of conditional transition
    - mapping of different Camera Objects 

*/
class CameraComponent : public Component
{
    ADD_SOLID_CLASS_METADATA(CameraComponent);

public:
    virtual void Init();
    virtual void Update(float delta);

private:
    void UpdateRatio(float dt);
private:
    Vec3 m_OwnerPrevPos;
    float m_Ratio;
};