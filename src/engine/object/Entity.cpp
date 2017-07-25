#pragma once
#include "Entity.h"

void Entity::Update(float delta)
{
	for(auto& component : m_Components)
	{
		component->Update(delta);
	}
}

void Entity::AddComponent(Component* component)
{ 
	m_Components.push_back(component);
	component->SetOwner(this);
}

void Entity::Init()
{
	for (auto component : m_Components)
	{
		component->Init();
	}
}
