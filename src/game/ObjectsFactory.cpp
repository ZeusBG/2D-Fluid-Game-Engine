#pragma once
#include "ObjectsFactory.h"
#include "engine/core/MetaData.h"
BaseObject* ObjectsFactory::CreteObject(const std::string& name)
{
    return MetaDataStorage::GetInstance()->Get(name)->CreateInstance<BaseObject>();
}
