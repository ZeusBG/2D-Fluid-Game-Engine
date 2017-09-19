#pragma once
#include "SimpleEntity.h"
#include "networking/networkutil/Buffer.h"
#include "networking/networkutil/networkutils.h"
#include "game/ObjectsFactory.h"

IMPLEMENT_METADATA(SimpleEntity);

SimpleEntity::SimpleEntity()
{
	AddComponent(ObjectsFactory::CreateComponent("CharacterControllerComponent"));
	AddComponent(ObjectsFactory::CreateComponent("CameraComponent"));
}

void SimpleEntity::Update(float delta)
{
    SimpleEntityBase::Update(delta);
}
SimpleEntity::~SimpleEntity()
{
}

void SimpleEntity::Serialize(ByteStream* bs)
{
	SimpleEntityBase::Serialize(bs);
}
void SimpleEntity::DeSerialize(ByteStream* bs)
{
	SimpleEntityBase::DeSerialize(bs);
}