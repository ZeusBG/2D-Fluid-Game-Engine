#pragma once
#include "../../util/Collections.h"
#include "../object/BaseObject.h"
#include "../object/Entity.h"
#include "IModule.h"

class World : public IModule
{
private:
    AVector<EntitySP> m_Entities;

    //AVector<Entity*> m_DynamicEntities;
    //AVector<Entity*> m_StaticEntities;

public:
    World();

    void Update(float delta);
    virtual void Init(Engine* engine);
    virtual const char* GetName();
    void Destroy();
    void AddEntity(std::shared_ptr<Entity>& entity) { entity->Init(); m_Entities.push_back(entity); }
    const AVector<EntitySP> GetVisibleEntities();

    const AVector<EntitySP>& GetEntities() const { return m_Entities; }
    
    virtual void Start() {}
    
    //const AVector<Entity*>& GetDynamicEntities() const { return m_DynamicEntities; }
    //const AVector<Entity*>& GetStaticEntities() const { return m_StaticEntities; }

    ~World();
};

