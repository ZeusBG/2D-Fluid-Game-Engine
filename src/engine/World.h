#pragma once
#include "../util/Collections.h"
#include "BaseObject.h"
#include "Entity.h"

class World
{
private:
	AVector<Entity> m_Entities;
	AVector<Entity*> m_DynamicEntities;
	AVector<Entity*> m_StaticEntities;

public:
	World();

	float update(float delta);

	AVector<Entity>& getEntities() { return m_Entities; }
	AVector<Entity*>& getDynamicEntities() { return m_DynamicEntities; }
	AVector<Entity*>& getStaticEntities() { return m_StaticEntities; }

	~World();
};

