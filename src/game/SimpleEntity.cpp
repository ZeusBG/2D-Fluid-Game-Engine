#pragma once
#include "SimpleEntity.h"

#include "game/ObjectsFactory.h"
IMPLEMENT_METADATA(SimpleEntity);
SimpleEntity::SimpleEntity()
{
    m_Transform.Scale(100.f);
}

void SimpleEntity::Update(float delta)
{
    Entity::Update(delta);
}
SimpleEntity::~SimpleEntity()
{
}