#pragma once
#include "ObjectsFactory.h"
#include "engine/object/Entity.h"
#include "engine/core/MetaData.h"
std::shared_ptr<Entity> ObjectsFactory::CreteEntity(const std::string& name)
{
    return std::static_pointer_cast<Entity>(MetaDataStorage::GetInstance()->Get(name)->CreateInstance());
}

std::shared_ptr<Entity> ObjectsFactory::CreateEntityFromJSON(const rapidjson::Value& json)
{
    EntitySP entity = std::static_pointer_cast<Entity>(MetaDataStorage::GetInstance()->Get(json["Class"].GetString())->CreateInstance());
    entity->DeSerialize(json["Class"]);
    const auto& components = json["Components"].GetArray();
    for (const auto& component : components)
    {
        auto& c = ObjectsFactory::CreateComponent(component["Component"].GetString());
        c->DeSerialize(component);
        entity->AddComponent(c);
    }
    return entity;
}

std::shared_ptr<Component> ObjectsFactory::CreateComponent(const std::string & name)
{
    return std::static_pointer_cast<Component>(MetaDataStorage::GetInstance()->Get(name)->CreateInstance());
}
