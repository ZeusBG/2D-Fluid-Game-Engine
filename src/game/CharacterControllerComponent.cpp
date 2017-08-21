#include "engine/core/Engine.h"
#include "engine/input/InputHandler.h"

#include "game/CharacterControllerComponent.h"

#include "util/math/Vec.h"

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
    
    m_Owner->AddTranslate(speed);
    sight = sight * 100; // Fix rotation please
    m_Owner->SetSight(sight);

    //if (InputHandler::Instance()->isMouseButtonJustPressed(MouseButton_LEFT))
    //{
    //    if (accShootDelay >= attackCooldown)
    //    {
    //        vec2 targetPos = InputHandler::Instance()->getMousePosition();
    //        vec2 pos = getPosition();
    //        vec2 direction = targetPos - pos;
    //        if (!direction.equalWithEpsilon(vec2Zero))
    //        {
    //            direction = direction.normalize();
    //            vec2 initialPos = pos + direction * 50.0f;
    //            Projectile* arrow = (Projectile *)getGameState<PlayState>()->getLevelData().createBaseObjectFromTemplateID("PlayerArrow", initialPos.x, initialPos.y);
    //            arrow->setDamage(damage);  //sets proper damage to arrow. Allows to be modified with power-ups.
    //            arrow->setSpeed(direction * arrow->getMaxVelocity() * projectileSpeedModifier);
    //            getGameState<GameState>()->addObject(arrow);

    //            visualComponent->setCurrentRenderSpriteByName("Shoot");
    //            visualComponent->getCurrentSpritePlaying()->play();
    //        }
    //        accShootDelay = 0.0f;
    //    }
    //}
}

CharacterControllerComponent::CharacterControllerComponent() :
    m_MoveVelocity(10.f),
    m_RotationVelocity(1.f)
{}