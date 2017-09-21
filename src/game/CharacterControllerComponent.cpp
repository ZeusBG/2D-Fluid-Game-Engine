#include "engine/core/Engine.h"
#include "engine/input/InputHandler.h"

#include "game/CharacterControllerComponent.h"
#include "engine/object/Transform.h"
#include "util/math/Vec.h"
#include "engine/camera/CameraHandler.h"
#include "engine/object/basecomponents/RigidBodyComponent.h"
IMPLEMENT_METADATA(CharacterControllerComponent)

void CharacterControllerComponent::Update(float dt)
{
    auto inputHandler = g_Engine->GetModule<InputHandler>();

    Vec2 speed;
    speed.x = ((float)inputHandler->IsKeyPressed(SDL_SCANCODE_D) - (float)inputHandler->IsKeyPressed(SDL_SCANCODE_A));
    speed.y = ((float)inputHandler->IsKeyPressed(SDL_SCANCODE_W) - (float)inputHandler->IsKeyPressed(SDL_SCANCODE_S));

    if (!speed.EqualWithEpsilon(Vec2::Zero))
        speed = speed * m_MoveVelocity;

    
    Vec2 sight = inputHandler->GetMousePosition();
    sight.Normalize();
    
    //istoilov : Make proper API calls
	m_Owner->GetComponent<RigidBodyComponent>()->ApplyLinearImpulse(speed);
    //m_Owner->AddTranslate(speed);
    sight = sight * 100; // Fix rotation please
    m_Owner->SetSight(sight);

	if (inputHandler->IsKeyPressed(SDL_SCANCODE_F))
		g_Engine->GetModule<CameraHandler>()->GetActiveCamera()->Zoom(5.0f);
	if (inputHandler->IsKeyPressed(SDL_SCANCODE_G))
		g_Engine->GetModule<CameraHandler>()->GetActiveCamera()->Zoom(-5.0f);
}

void CharacterControllerComponent::Init()
{
}

CharacterControllerComponent::CharacterControllerComponent() :
    m_MoveVelocity(1000.f),
    m_RotationVelocity(1.f)
{}