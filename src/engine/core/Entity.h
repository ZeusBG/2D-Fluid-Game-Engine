#pragma once
#include "../../util/Collections.h"
#include "Component.h"
#include "../Transform.h"
class Entity : public BaseObject
{
	Transform m_Transform;
	AVector<Component> m_Components;
public:
	Entity() {}
	~Entity() {}
};

