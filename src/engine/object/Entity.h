#pragma once
#include "../../util/Collections.h"
#include "Component.h"
#include "../Transform.h"
#include <memory>

class Entity : public BaseObject
{
protected:
    Transform m_Transform;
    AVector<Component*> m_Components;
public:
    virtual void AddComponent(Component* component);
    virtual void Update(float delta);
    virtual void Init();
    
    const Transform& GetTransform() { return m_Transform; }

    inline void AddTranslate(const Vec2& dir) { m_Transform.Translate(dir.x, dir.y); }
    void SetSight(const Vec2& sight);

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

