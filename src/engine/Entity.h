#pragma once
#include "../util/Collections.h"
#include "Component.h"
class Entity : public BaseObject
{
	AVector<Component> m_Components;
public:
	Entity() {}
	~Entity() {}
};

