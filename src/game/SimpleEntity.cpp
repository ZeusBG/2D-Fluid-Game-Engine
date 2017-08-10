#pragma once
#include "SimpleEntity.h"

#include "game/SimpleVisualComponent.h"
#include "game/CharacterControllerComponent.h"

#include "engine/rendering/shaderobjects/SimplePS.h"
#include "engine/rendering/shaderobjects/SimpleVS.h"
#include "game/ObjectsFactory.h"
IMPLEMENT_METADATA(SimpleEntity);

SimpleEntity::SimpleEntity()
{
    //ComponentSharedPtr c(new SimpleVisualComponent());
    AddComponent(ObjectsFactory::CreateComponent("SimpleVisualComponent"));
    AddComponent(ObjectsFactory::CreateComponent("CharacterControllerComponent"));
}

void SimpleEntity::Update(float delta)
{
    Entity::Update(delta);
}
SimpleEntity::~SimpleEntity()
{
}