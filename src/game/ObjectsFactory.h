#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include "rapidjson/document.h"
class Component;
class Entity;

class ObjectsFactory
{
	// TODO Add a pool for reusable objects;
public:
	static std::unordered_map<int, const rapidjson::Value*> s_IDToJSON;
	static rapidjson::Document s_ProtoypeDocument;

	static void LoadPrototypeFile(const char* file);
	static std::shared_ptr<Entity> CreateEntityFromType(int type);
    static std::shared_ptr<Entity> CreteEntity(const std::string& name);
    static std::shared_ptr<Entity> CreateEntityFromJSON(const rapidjson::Value& json);
    static std::shared_ptr<Component> CreateComponent(const std::string& name);
};

