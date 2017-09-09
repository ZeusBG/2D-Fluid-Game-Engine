#pragma once
#include "SimpleEntity.h"
#include "networking/networkutil/Buffer.h"
#include "networking/networkutil/networkutils.h"
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

void SimpleEntity::Serialize(ByteStream* buffer)
{
	buffer->BeginCommand(NetCommand::UpdateEntity);
	buffer->AddData(&m_ID, sizeof(int));
	SerializeTransform(&m_Transform, buffer);
}
void SimpleEntity::DeSerialize(ByteStream* buffer)
{
	DeSerializeTransform(&m_Transform, buffer);
}