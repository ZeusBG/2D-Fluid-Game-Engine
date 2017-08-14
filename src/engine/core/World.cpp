#pragma once
#include "World.h"
#include "game/ObjectsFactory.h"
World::World() {};
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

const AVector<EntitySP> World::GetVisibleEntities()
{
	return m_Entities;
}
