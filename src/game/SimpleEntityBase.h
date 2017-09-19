#pragma once
#include <memory>
#include "../engine/core/Engine.h"
#include "../engine/core/SystemSettings.h"


class SimpleEntityBase : public Entity
{
    ADD_SOLID_CLASS_METADATA(SimpleEntityBase)
public:
	static const int SIMPLE_ENTITY_ID = 2;
	SimpleEntityBase();
    virtual ~SimpleEntityBase();
    virtual void Update(float delta);
	virtual void Serialize(ByteStream* buffer) override;
	virtual void DeSerialize(ByteStream* buffer) override;
	virtual int GetTypeID() const override { return SIMPLE_ENTITY_ID; }
};

using SimpleEntityBaseSP = std::shared_ptr<SimpleEntityBase>;
