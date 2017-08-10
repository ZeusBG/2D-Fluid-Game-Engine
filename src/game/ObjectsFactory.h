#pragma once
#include <string>
#include <memory>
class Component;
class BaseObject;

class ObjectsFactory
{
public:
    static std::shared_ptr<BaseObject> CreteObject(const std::string& name);
    static std::shared_ptr<Component> CreateComponent(const std::string& name);
};

