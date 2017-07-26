#pragma once
#include "../../util/Collections.h"
#include "Component.h"
#include "../Transform.h"
#include <memory>

class Entity : public BaseObject
{
	Transform m_Transform;
	AVector<Component*> m_Components;
public:
	Entity() {}
	virtual void AddComponent(Component* component);
	virtual void Update(float delta);
	virtual void Init();
	template <typename T>
	T* GetComponent()
	{
		for (Component* component : m_Components)
		{
			T* result = dynamic_cast<T*>(component);
			if (result)
				return result;
		}
		return nullptr;
	}
};

typedef std::shared_ptr<Entity> EntitySharedPtr;

