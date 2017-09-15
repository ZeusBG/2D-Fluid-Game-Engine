#pragma once
#include "World.h"
#include "game/ObjectsFactory.h"
#include "networking/networkutil/Buffer.h"
#include <algorithm>

World::World() {};
void World::DoSnapShot(ByteStream* bs)
{
	const short numEntities = m_Entities.size();
	bs->AddData(&numEntities, sizeof(short));
	for (const auto& entity : m_Entities)
	{
		entity->Serialize(bs);
	}
}
void World::DoCreationSnapShot(ByteStream * bs)
{
	const short numEntities = m_Entities.size();
	bs->AddData(&numEntities, sizeof(short));
	for (const auto& entity : m_Entities)
	{
		int entityTypeID = entity->GetTypeID();
		int entityID = entity->GetID();
		bs->AddData(&entityID, sizeof(int));
		bs->AddData(&entityTypeID, sizeof(int));
	}
}
World::~World() {};

void World::Update(float delta)
{
	for (EntitySP& e : m_Entities)
	{
		e->Update(delta);
	}
}

void World::Init(Engine* engine)
{
}

const char* World::GetName() { return "World"; }

void World::Destroy()
{
    for (EntitySP& e : m_Entities)
    {
        e->Destroy();
    }
	m_Entities.clear();
	m_IDToEntityMap.clear();
}

void World::LoadLevel(const rapidjson::Value& val)
{
    auto& entities = val["Entities"].GetArray();
    for (auto& el : entities)
    {
        auto& entity = ObjectsFactory::CreateEntityFromJSON(el);
        AddEntity(entity);
    }
}

void World::AddEntity(std::shared_ptr<Entity>& entity)
{
	entity->Init();
	m_Entities.push_back(entity);
	m_IDToEntityMap.insert({ entity->GetID(), entity });
}

EntitySP World::GetEntityByID(int id)
{
	auto entity = m_IDToEntityMap.find(id);
	if (entity != m_IDToEntityMap.end())
		return entity->second;
	return nullptr;
}

const AVector<EntitySP> World::GetVisibleEntities()
{
	return m_Entities;
}

bool World::RemoveEntityByID(int id)
{
	auto entity = m_IDToEntityMap.find(id);
	if (entity == m_IDToEntityMap.end())
		return false;
	EntitySP entityPtr = entity->second;
	m_IDToEntityMap.erase(id);
	m_Entities.erase(std::remove(m_Entities.begin(), m_Entities.end(), entityPtr));
	return true;
}
