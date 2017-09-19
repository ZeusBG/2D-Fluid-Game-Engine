#pragma once
#include "Physics.h"
#include <Box2D\Box2D.h>
Physics::Physics()
{
	m_PhysicsWorld.reset(new b2World({ 0.0, -100.0f }));
}
Physics::~Physics() {}

void Physics::Init(Engine* engine)
{
}

void Physics::Update(float delta)
{
	m_PhysicsWorld->Step(delta, 6, 3);
}

void Physics::DestroyObject(b2Body* object)
{
	m_PhysicsWorld->DestroyBody(object);
}

b2Body* Physics::CreateObject(const b2BodyDef& def)
{
	return m_PhysicsWorld->CreateBody(&def);
}
