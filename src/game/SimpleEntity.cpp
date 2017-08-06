#pragma once
#include "SimpleEntity.h"

#include "game/ObjectsFactory.h"
IMPLEMENT_METADATA(SimpleEntity);
SimpleEntity::SimpleEntity()
{
    m_Transform.Scale(100.f);
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