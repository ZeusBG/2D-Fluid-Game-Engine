#pragma once
#include "BaseObject.h"
#include <memory>
class Entity;
class Component : public BaseObject
{

protected:
    Entity* m_Owner;

public:
    void SetOwner(Entity* newOwner) { m_Owner = newOwner; }

    Entity* GetOwner() { return m_Owner; }
};

typedef std::shared_ptr<Component> ComponentSharedPtr;