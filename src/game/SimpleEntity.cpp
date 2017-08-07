#pragma once
#include "SimpleEntity.h"

#include "game/SimpleVisualComponent.h"
#include "game/CharacterControllerComponent.h"

#include "engine/rendering/shaderobjects/SimplePS.h"
#include "engine/rendering/shaderobjects/SimpleVS.h"

IMPLEMENT_METADATA(SimpleEntity);

SimpleEntity::SimpleEntity()
{
    //ComponentSharedPtr c(new SimpleVisualComponent());
    AddComponent(new SimpleVisualComponent());
    AddComponent(new CharacterControllerComponent());
}

void SimpleEntity::Update(float delta)
{
    Entity::Update(delta);

    //m_Transform.Translate(0.001f, 0.001f);
}