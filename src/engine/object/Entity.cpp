#pragma once
#include "Entity.h"
#include <rapidjson/document.h>

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

void Entity::DeSerializeFromJSON(const rapidjson::Value& val)
{
	if (val.HasMember("Transform"))
	{
		const auto& transform = val["Transform"];
		const auto& position = transform["Position"].GetArray();
		m_Transform.SetTranslate({ position[0].GetFloat(), position[1].GetFloat() });
		const auto& scale = transform["Scale"].GetArray();
		m_Transform.Scale(scale[0].GetFloat(), scale[1].GetFloat());
	}
}

std::shared_ptr<Component> Entity::GetComponentByName(const char* name)
{
	for (const auto& component : m_Components)
	{
		if (component->GetName() == name)
			return component;
	}
	return nullptr;
}
