#pragma once
#include <memory>
#include "game/SimpleEntityBase.h"

class SimpleEntity : public SimpleEntityBase
{
    ADD_SOLID_CLASS_METADATA(SimpleEntity)
public:
	static const int SIMPLE_ENTITY_ID = 3;
    SimpleEntity();
    virtual ~SimpleEntity();
    virtual void Update(float delta);
	virtual void Serialize(ByteStream* buffer) override;
	virtual void DeSerialize(ByteStream* buffer) override;
	virtual int GetTypeID() const override { return SIMPLE_ENTITY_ID; }
};

using SimpleEntitySP = std::shared_ptr<SimpleEntity>;
