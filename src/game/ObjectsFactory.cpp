#pragma once
#include "ObjectsFactory.h"
#include "engine/core/MetaData.h"
std::shared_ptr<BaseObject> ObjectsFactory::CreteObject(const std::string& name)
{
    return std::static_pointer_cast<BaseObject>(MetaDataStorage::GetInstance()->Get(name)->CreateInstance<BaseObject>());
}
