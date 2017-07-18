#pragma once
#include "World.h"

World::World() {};
World::~World() {};

float World::update(float delta)
{
	for (Entity& e : m_Entities)
	{
		e.Update(delta);
	}
}