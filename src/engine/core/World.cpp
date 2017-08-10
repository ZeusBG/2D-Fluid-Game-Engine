#pragma once
#include "World.h"

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

const AVector<EntitySP> World::GetVisibleEntities()
{
	return m_Entities;
}
