#pragma once
#include "ObjectsFactory.h"
#include "engine/object/Entity.h"
#include "engine/core/MetaData.h"
#include <rapidjson/istreamwrapper.h>
#include "rapidjson/document.h"
#include <fstream>

std::unordered_map<int,const rapidjson::Value*> ObjectsFactory::s_IDToJSON;
rapidjson::Document ObjectsFactory::s_ProtoypeDocument;

void ObjectsFactory::LoadPrototypeFile(const char* file)
{
	std::ifstream ifs(file);
	bool t = ifs.good();
	rapidjson::IStreamWrapper isw(ifs);

	s_ProtoypeDocument.ParseStream(isw);

	const auto& entities = s_ProtoypeDocument["Entities"].GetArray();
	for (const auto& entity : entities)
	{
		const auto& val = entity["Class"];
		int id = entity["ID"].GetInt();
		s_IDToJSON.insert({ id, &entity });
	}

}
std::shared_ptr<Entity> ObjectsFactory::CreateEntityFromType(int type)
{
	auto& entitiyIt = s_IDToJSON.find(type);
	if (entitiyIt == s_IDToJSON.end())
		return nullptr;
	return CreateEntityFromJSON(*(entitiyIt->second));
}
std::shared_ptr<Entity> ObjectsFactory::CreteEntity(const std::string& name)
{
    return std::static_pointer_cast<Entity>(MetaDataStorage::GetInstance()->Get(name)->CreateInstance());
}

std::shared_ptr<Entity> ObjectsFactory::CreateEntityFromJSON(const rapidjson::Value& json)
{
    EntitySP entity = std::static_pointer_cast<Entity>(MetaDataStorage::GetInstance()->Get(json["Class"].GetString())->CreateInstance());
    entity->DeSerializeFromJSON(json);
    const auto& components = json["Components"].GetArray();
    for (const auto& component : components)
    {
		const auto& coponentInfo = component["Component"];
		auto entityComponent = entity->GetComponentByName(coponentInfo["Class"].GetString());
		if (entityComponent != nullptr)
		{
			entityComponent->DeSerializeFromJSON(coponentInfo);
		}
		else
		{
			// In case somebody added a component, which
			// is not from the defualt ones for this entity
			auto& c = ObjectsFactory::CreateComponent(coponentInfo["Class"].GetString());
			entity->AddComponent(c);
			c->DeSerializeFromJSON(coponentInfo);
		}
    }
    return entity;
}

std::shared_ptr<Component> ObjectsFactory::CreateComponent(const std::string& name)
{
    return std::static_pointer_cast<Component>(MetaDataStorage::GetInstance()->Get(name)->CreateInstance());
}
