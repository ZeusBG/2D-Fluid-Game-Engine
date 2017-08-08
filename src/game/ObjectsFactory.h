#pragma once
#include <string>
#include <memory>
class BaseObject;

class ObjectsFactory
{
public:
    static std::shared_ptr<BaseObject> CreteObject(const std::string& name);
};

