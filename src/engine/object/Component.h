#pragma once
class Entity;
class Component : public BaseObject
{
	Entity* m_Owner;
public:
	void SetOwner(Entity* newOwner) { m_Owner = newOwner; }

	Entity* GetOwner() { return m_Owner; }
};