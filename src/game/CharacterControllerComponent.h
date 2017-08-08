#pragma once
#include "engine/object/Component.h"


/*
TODO istoilov :
    - implement key maping to actions / remove hard-coded keys
    - make component aplicable to multiple entities
    - figure out loading from file mechanism
    - move move/rotation velocity to physics component 
*/

class CharacterControllerComponent : public Component
{
    ADD_SOLID_CLASS_METADATA(CharacterControllerComponent)
public:
    CharacterControllerComponent();

    virtual void Update(float dt);

private:
    //unit type : m/s
    float m_MoveVelocity;

    //unit type : ??
    float m_RotationVelocity;
};

using CharacterControllerComponentSP = std::shared_ptr<CharacterControllerComponent>;
