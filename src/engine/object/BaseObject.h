#pragma once
#include "engine/core/MetaData.h"
#include "rapidjson/document.h"

class BaseObject : public std::enable_shared_from_this<BaseObject>
{
public:
    virtual void Init() {}

    virtual ~BaseObject() {}
    virtual void Update(float delta) = 0;
    virtual void BeginPlay() {}
    virtual void Destroy() {};
    virtual void DeSerialize(const rapidjson::Value& val) {}
};

using BaseObjectSP = std::shared_ptr<BaseObject>;

