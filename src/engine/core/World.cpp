#pragma once
#include "World.h"

World::World() {};
World::~World() {};

void World::Update(float delta)
{
	for (EntitySharedPtr& e : m_Entities)
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
}

const AVector<EntitySharedPtr> World::GetVisibleEntities()
{
	return m_Entities;
}
