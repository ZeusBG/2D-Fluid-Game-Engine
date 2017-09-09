#pragma once
#include "Entity.h"

IMPLEMENT_METADATA(Entity);

int Entity::s_IDGen = 0;
void Entity::Update(float delta)
{
    for(auto& component : m_Components)
    {
        component->Update(delta);
    }
}

Entity::Entity()
{
	m_ID = s_IDGen++;
}

Entity::Entity(const Entity& other)
{
	m_ID = s_IDGen++;
}

void Entity::AddComponent(ComponentSP component)
{ 
    m_Components.push_back(component);
    component->SetOwner(this);
}

void Entity::Init()
{
    for (const auto& component : m_Components)
    {
        component->Init();
    }
}

void Entity::Destroy()
{
    for (const auto& component : m_Components)
    {
        component->Destroy();
    }
}

void Entity::SetSight(const Vec2& sight)
{
    m_Transform.SetSight(sight);
}