#pragma once
#include <string>
class BaseObject;

class ObjectsFactory
{
public:
    static BaseObject* CreteObject(const std::string& name);
};

