#pragma once
#include "../util/Collections.h"
#include "BaseObject.h"
#include "Entity.h"
#include "Interface.h"

class World : public Interface
{
private:
	AVector<Entity> m_Entities;
	AVector<Entity*> m_DynamicEntities;
	AVector<Entity*> m_StaticEntities;

public:
	World();

	void Update(float delta);
	virtual void Init(Engine* engine);
	virtual const char* GetName();

	AVector<Entity>& getEntities() { return m_Entities; }
	AVector<Entity*>& getDynamicEntities() { return m_DynamicEntities; }
	AVector<Entity*>& getStaticEntities() { return m_StaticEntities; }

	~World();
};

