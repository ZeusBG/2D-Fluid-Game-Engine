#pragma once
#include <memory>
#include "../engine/core/Engine.h"
#include "../engine/core/SystemSettings.h"

class SimpleEntity : public Entity
{
public:
	SimpleEntity();
	virtual void Update(float delta);
};

