#pragma once
#include "World.h"

World::World() {};
World::~World() {};

void World::Update(float delta)
{
	for (Entity& e : m_Entities)
	{
		e.Update(delta);
	}
}

void World::Init(Engine* engine)
{
}


const char* World::GetName() { return "World"; }

void World::Destroy()
{
}
