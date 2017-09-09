#pragma once
#include <memory>
#include "../engine/core/Engine.h"
#include "../engine/core/SystemSettings.h"


class SimpleEntity : public Entity
{
    ADD_SOLID_CLASS_METADATA(SimpleEntity)
public:
    SimpleEntity();
    virtual ~SimpleEntity();
    virtual void Update(float delta);
	virtual void Serialize(ByteStream* buffer) override;
	virtual void DeSerialize(ByteStream* buffer) override;
};

using SimpleEntitySP = std::shared_ptr<SimpleEntity>;
