#pragma once
#include "../../util/Collections.h"
#include "../object/BaseObject.h"
#include "../object/Entity.h"
#include "IModule.h"
#include "rapidjson/document.h"

struct ByteStream;

class World : public IModule
{
private:
    AVector<EntitySP> m_Entities;
	std::unordered_map<int, EntitySP> m_IDToEntityMap;
    //AVector<Entity*> m_DynamicEntities;
    //AVector<Entity*> m_StaticEntities;

public:
    World();

    void Update(float delta);
    virtual void Init(Engine* engine);
    virtual const char* GetName();
    void Destroy();
    void LoadLevel(const rapidjson::Value& val);
	void AddEntity(std::shared_ptr<Entity>& entity);

	EntitySP GetEntityByID(int id);
    const AVector<EntitySP> GetVisibleEntities();
    const AVector<EntitySP>& GetEntities() const { return m_Entities; }
	bool RemoveEntityByID(int id);

    virtual void Start() {}

	void DoSnapShot(ByteStream* stream);
    //const AVector<Entity*>& GetDynamicEntities() const { return m_DynamicEntities; }
    //const AVector<Entity*>& GetStaticEntities() const { return m_StaticEntities; }

    ~World();
};

