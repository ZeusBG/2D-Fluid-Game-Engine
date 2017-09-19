#pragma once
#include "../core/IModule.h"
#include "util/Collections.h"


class Component;
class b2Body;
class b2World;
struct b2BodyDef;


struct b2WorldDeleter
{
	void operator()(b2World* world)
	{
		delete world;
	}
};

class Physics : public IModule
{
public:
    Physics();
    ~Physics();

	virtual void Init(Engine* engine) override;
    void Update(float delta) override;

	virtual void Start() override {}
	virtual void Destroy() override {};
	virtual const char* GetName() override { return "Physics"; }

	void DestroyObject(b2Body* object);
	b2Body* CreateObject(const b2BodyDef& def);
private:
    AVector<std::shared_ptr<Component>> m_Components;
	std::unique_ptr<b2World, b2WorldDeleter> m_PhysicsWorld;
};
