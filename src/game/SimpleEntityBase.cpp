#pragma once
#include "SimpleEntityBase.h"
#include "networking/networkutil/Buffer.h"
#include "networking/networkutil/networkutils.h"
#include "game/ObjectsFactory.h"

IMPLEMENT_METADATA(SimpleEntityBase);

SimpleEntityBase::SimpleEntityBase()
{
	AddComponent(ObjectsFactory::CreateComponent("RigidBodyComponent"));
	AddComponent(ObjectsFactory::CreateComponent("SimpleVisualComponent"));
}

void SimpleEntityBase::Update(float delta)
{
    Entity::Update(delta);
}
SimpleEntityBase::~SimpleEntityBase()
{
}

void SimpleEntityBase::Serialize(ByteStream* bs)
{
	bs->AddData(&m_ID, sizeof(int));
	SerializeTransform(&m_Transform, bs);
}
void SimpleEntityBase::DeSerialize(ByteStream* buffer)
{
	DeSerializeTransform(&m_Transform, buffer);
}