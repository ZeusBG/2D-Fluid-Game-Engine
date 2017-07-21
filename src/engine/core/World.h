#pragma once
#include "../../util/Collections.h"
#include "../object/BaseObject.h"
#include "../object/Entity.h"
#include "IModule.h"

class World : public IModule
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
	virtual void Destroy();

	const AVector<Entity>& GetEntities() const { return m_Entities; }
	const AVector<Entity*>& GetDynamicEntities() const { return m_DynamicEntities; }
	const AVector<Entity*>& GetStaticEntities() const { return m_StaticEntities; }

	~World();
};

