#pragma once
#include "rapidjson/fwd.h"
#include <memory>

struct ByteStream;

class BaseObject : public std::enable_shared_from_this<BaseObject>
{
public:
    virtual void Init() {}

    virtual ~BaseObject() {}
    virtual void Update(float delta) = 0;
    virtual void BeginPlay() {}
    virtual void Destroy() {};
    virtual void DeSerializeFromJSON(const rapidjson::Value& val) {}
	virtual void Serialize(ByteStream* buffer) {}
	virtual void DeSerialize(ByteStream* buffer) {}
};

using BaseObjectSP = std::shared_ptr<BaseObject>;

