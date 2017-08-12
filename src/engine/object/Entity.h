#pragma once
#include "util/Collections.h"

#include "engine/object/basecomponents/Component.h"
#include "engine/object/Transform.h"

#include <memory>

class Entity : public BaseObject
{
    ADD_SOLID_CLASS_METADATA(Entity)
protected:
    Transform m_Transform;
    AVector<ComponentSP> m_Components;
public:
    virtual void AddComponent(ComponentSP component);
    virtual void Update(float delta);
    virtual void Init();
    virtual void Destroy();
        
    inline const Transform& GetTransform() { return m_Transform; }
    inline Vec2 GetGlobalPosition() const { return m_Transform.GetTranslate(); }
    inline Vec3 GetGlobalPosition3() const { return m_Transform.GetTranslate3(); }

    inline void AddTranslate(const Vec2& dir) { m_Transform.Translate(dir.x, dir.y); }
    void SetSight(const Vec2& sight);

    Vec2 GetSight() const { return m_Transform.GetSight(); }
    Vec3 GetSight3() const { return m_Transform.GetSight3(); }


    template <typename T>
    std::shared_ptr<T> GetComponent()
    {
        for (const auto& component : m_Components)
        {
            std::shared_ptr<T> result = dynamic_pointer_cast<T>(component);
            if (result.get())
                return result;
        }
        return nullptr;
    }

};

using EntitySP = std::shared_ptr<Entity>;
