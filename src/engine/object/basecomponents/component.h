#pragma once
#include "engine/object/BaseObject.h"
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

using ComponentSP = std::shared_ptr<Component>;
