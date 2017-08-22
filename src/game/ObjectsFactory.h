#pragma once
#include <string>
#include <memory>
#include "rapidjson/document.h"
class Component;
class Entity;

class ObjectsFactory
{
public:
    static std::shared_ptr<Entity> CreteEntity(const std::string& name);
    static std::shared_ptr<Entity> CreateEntityFromJSON(const rapidjson::Value& json);
    static std::shared_ptr<Component> CreateComponent(const std::string& name);
};

